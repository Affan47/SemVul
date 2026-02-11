set_show_disconnected(bool show_disconnected)
{
	if(show_disconnected)
	{
		m_filter_model.reset();
		m_view.set_model(m_store);
	}
	else
	{
		m_filter_model = Gtk::TreeModelFilter::create(m_store);
		m_view.set_model(m_filter_model);

		m_filter_model->set_visible_func(
			sigc::mem_fun(*this, &UserList::visible_func));
	}
}
