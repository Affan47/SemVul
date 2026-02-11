log_func (Group g_, size_t indent_level_, const string&  func_name_,
		  marker_t type_)
{
    if (m_state == closed) {
		errno = EPERM;
		return -1;
    }

    if (! group_enabled (g_)) {
		return 0;
    }

    m_bytecount += add_timestamp (m_sink);
    m_bytecount += indent_func_name (m_sink, func_name_, indent_level_, type_);
    m_sink << ((type_ == FUNC_ENTRY) ? "---v---\n" : "---^---\n") << std::flush;
    m_bytecount += ::strlen ("---v---\n");

	return handle_rollover ();
}
