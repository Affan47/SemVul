collectStylesheet(const boost::optional<ID_t> &id, const boost::optional<ID_t> &parent)
{
  if (m_collecting)
  {
    assert(m_currentStylesheet);

    if (parent)
      m_currentStylesheet->parent = m_dict.stylesheets[get(parent)];

    if (id)
      m_dict.stylesheets[get(id)] = m_currentStylesheet;

    for_each(m_newStyles.begin(), m_newStyles.end(), boost::bind(&KEYStyle::link, _1, m_currentStylesheet));

    m_currentStylesheet.reset(new KEYStylesheet());
    m_newStyles.clear();
    m_currentPlaceholderStyle.reset();
  }
}
