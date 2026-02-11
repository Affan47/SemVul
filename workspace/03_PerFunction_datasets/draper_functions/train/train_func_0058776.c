AddFileTheme (Theme *theme, char const *label)
{
	string name = theme->GetName ().c_str ();
	if (name == "Default")
		name = "GChemPaint";
	string theme_name = name;
	if (m_Themes.find (name) != m_Themes.end ()) {
		name = string ((label)? label: _("Unknown")) + ":" + name;
	}
	int i = 0;
	while (m_Themes.find (name) != m_Themes.end ())
		name = string ((label)? label: _("Unknown")) + ((char) ('0' + i++)) + ":" + theme_name;
	m_Themes[name] = theme;
	m_Names.push_back (name);
}
