set_title_translation(const Glib::ustring& locale, const Glib::ustring& translation)
{
  if(translation.empty())
  {

    type_map_locale_to_translations::iterator iterFind = m_map_translations.find(locale);
    if(iterFind != m_map_translations.end())
      m_map_translations.erase(iterFind);
  }
  else
    m_map_translations[locale] = translation;
}
