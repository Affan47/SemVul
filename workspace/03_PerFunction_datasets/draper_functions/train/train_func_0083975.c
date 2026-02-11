GetLocalizedString (char const *lang) const
{
	string s;
	if (lang)
		s = const_cast<LocalizedStringValue*> (this)->vals[lang];
	return (s.length () > 0)? s.c_str (): GetAsString ();
}

}
