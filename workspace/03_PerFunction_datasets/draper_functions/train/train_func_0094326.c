result_item_single_get_buffer(result_item_t * item, poldiff_form_e form)
{
	util_text_buffer_clear(single_buffer);
	if (form == POLDIFF_FORM_NONE) {
		result_item_print_summary(item, single_buffer);
	} else {
		result_item_print_header(item, single_buffer, form);
		result_item_print_diff(item, single_buffer, form);
	}
	return single_buffer;
}
