result_item_type_get_forms(result_item_t * item, int forms[5])
{
	result_item_single_get_forms(item, forms);
	if (!item->data.type_can_modify) {
		forms[4] = -1;
	}
}
