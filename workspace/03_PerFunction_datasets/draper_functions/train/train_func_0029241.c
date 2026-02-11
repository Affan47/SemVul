on_toolbutton_del_reflection_clicked(void)
{
	LOG;

	HklSample * sample;

	sample = _samples->current;
	if(sample){
		Glib::RefPtr<Gtk::TreeSelection> selection = _treeViewReflections->get_selection();
		unsigned int nb_rows = selection->count_selected_rows();
		if (nb_rows){
			Gtk::TreeSelection::ListHandle_Path list = selection->get_selected_rows();
			Gtk::TreeSelection::ListHandle_Path::iterator iter = list.begin();
			Gtk::TreeSelection::ListHandle_Path::iterator last = list.end();
			Glib::RefPtr<Gtk::ListStore> liststore = _mapReflectionModel[sample->name];

			std::vector<unsigned int> indexes;
			while(iter != last){
				Gtk::ListStore::Row row = *(liststore->get_iter(*iter));
				indexes.push_back(row[_reflectionModelColumns.index]);
				++iter;
			}
			std::ostringstream os;
			os << "Are you sure you want to delete reflections :";
			for(unsigned int i=0; i< indexes.size();i++)
				os << " " << indexes[i];

			_message = new Gtk::MessageDialog("", false,
							   Gtk::MESSAGE_WARNING,
							   Gtk::BUTTONS_YES_NO);
			_message->set_message(os.str());
			_message->show();
			int respons = _message->run();
			switch (respons){
			case Gtk::RESPONSE_YES:
				for(unsigned int i=0;i<indexes.size();i++){

					unsigned int index = indexes[i] - i;
					hkl_sample_del_reflection(sample, index);
				}
				this->updateReflections(sample, liststore);
				break;
			}
			delete _message;
		}else
			_statusBar->push("Please select at least one reflection.");
	}
}
