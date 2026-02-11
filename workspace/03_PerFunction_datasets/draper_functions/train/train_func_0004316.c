s_cell_border_style (PP_PropertyMap::Line & line, const PP_PropertyMap::Line & table_line,
						  const fl_TableLayout * table)
{
	if (line.m_t_color == PP_PropertyMap::color_inherit)
		{
			line.m_t_color = table_line.m_t_color;
			if (line.m_t_color == PP_PropertyMap::color_color)
				line.m_color = table_line.m_color;
		}
	if ((line.m_t_color == PP_PropertyMap::color_inherit) ||
		(line.m_t_color == PP_PropertyMap::color__unset))
		{
			line.m_t_color = PP_PropertyMap::color_color;
			line.m_color = table->getDefaultColor ();
		}

	if (line.m_t_linestyle == PP_PropertyMap::linestyle_inherit)
		line.m_t_linestyle = table_line.m_t_linestyle;
	if ((line.m_t_linestyle == PP_PropertyMap::linestyle_inherit) ||
		(line.m_t_linestyle == PP_PropertyMap::linestyle__unset))
		line.m_t_linestyle = PP_PropertyMap::linestyle_solid;

	if (line.m_t_thickness == PP_PropertyMap::thickness_inherit)
		{
			line.m_t_thickness = table_line.m_t_thickness;
			if (line.m_t_thickness == PP_PropertyMap::thickness_length)
				line.m_thickness = table_line.m_thickness;
		}
	if ((line.m_t_thickness == PP_PropertyMap::thickness_inherit) ||
		(line.m_t_thickness == PP_PropertyMap::thickness__unset))
		{
			line.m_t_thickness = table_line.m_t_thickness;
			UT_sint32 defaultThickness = table->getLineThickness ();
			line.m_thickness = (defaultThickness > 0) ? static_cast<UT_uint32>(defaultThickness) : 0;
		}


	if ((line.m_thickness == 0) || (line.m_t_color == PP_PropertyMap::color_transparent))
		{
			line.m_t_linestyle = PP_PropertyMap::linestyle_none;
		}
}
