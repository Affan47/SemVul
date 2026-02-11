result_item_save_current_line(result_item_t * item, poldiff_form_e form, gint offset)
{

	if (form != POLDIFF_FORM_NONE) {
		item->offsets[form_reverse_map[form]] = offset;
	}
}
