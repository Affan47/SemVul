stl_styleinfo_style_siblings(StyleInfo *si, Style *stla, Style *stlb)
{
	if((si != NULL) && (stla != NULL) && (stlb != NULL))
	{
		GNode	*na, *nb;

		na = styleinfo_style_get_node(si, stla);
		nb = styleinfo_style_get_node(si, stlb);

		return na->parent == nb->parent;
	}
	return FALSE;
}
