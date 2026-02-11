showNextWords()
{
	refmc->clear();
	for (int i = 0; i < words_in_list; i++) {
		(Gtk::TreeModel::Row (*(refmc->append())))[mc.col_name] = to_utf8(dict->getWord(false));


		if (!dict->goToNextWord()) {
			break;
		}
	}

	return true;
}
