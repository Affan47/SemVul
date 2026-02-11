get_new_subject()
{
    if( m_show_entry_new_subject && m_entry_new_subject ) return m_entry_new_subject->get_text();

    return std::string();
}
