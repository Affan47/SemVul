getAreaFromCharacter(const wchar_t c, bool* fallback_font) const
	{
		const int area_id = getAreaIDFromCharacter(c, fallback_font);
		const bool use_fallback_font = (fallback_font && *fallback_font);


		return ( use_fallback_font ? m_fallback_font->Areas[area_id] : Areas[area_id]);
	}
