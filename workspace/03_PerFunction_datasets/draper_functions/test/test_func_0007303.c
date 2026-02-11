OnForeColorChanged (GOColor color)
{
	m_Color = color;
	BuildTagsList ();
	if (m_Active) {
		gccv::TextTagList l;
		l.push_front (new gccv::ForegroundTextTag (m_Color));
		m_Active->ApplyTagsToSelection (&l);
	}
}
