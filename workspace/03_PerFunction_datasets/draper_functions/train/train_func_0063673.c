add(const std::string& str)
{
	if(!str.empty())
	{
		Gtk::TreeIter iter = m_history.m_history->append();
		(*iter)[m_history.m_history_columns.text] = str;
	}
}
