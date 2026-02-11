append_markup (PangoAttribute *src, TXORun *run)
{
	if (run->last > run->first) {
		PangoAttribute *dst = pango_attribute_copy (src);
		dst->start_index = run->first;
		dst->end_index = run->last;
		pango_attr_list_change (run->accum, dst);
	}
	return FALSE;
}
