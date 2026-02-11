setBackground (const PP_PropertyMap::Background & style)
{
	m_background = style;
	PP_PropertyMap::Background background = m_background;
	if(background.m_t_background == PP_PropertyMap::background_solid)
	{
		getFillType().setColor(background.m_color);
	}
}
