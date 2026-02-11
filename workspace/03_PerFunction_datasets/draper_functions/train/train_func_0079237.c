m_prepare_submixed()
{
    unsigned int bound = share();

    if(m_skill & chars1)
	m_strings += randstring(group_chars1, bound);

    if(m_skill & chars2)
	m_strings += randstring(group_chars2, bound);

    if(m_skill & chars3)
	m_strings += randstring(group_chars3, bound);

    if(m_skill & chars4)
	m_strings += randstring(group_chars4, bound);

    if(m_skill & chars5)
	m_strings += randstring(group_chars5, bound);

    if(m_skill & numbrs)
	m_strings += randstring(group_numbrs, bound);

    m_strings = m_strings.substr(0, m_num_chars * m_num_strings);
}
