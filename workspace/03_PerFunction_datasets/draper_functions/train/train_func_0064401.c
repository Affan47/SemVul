lookup_exception(struct level_validator *this, void *opaque_data)
{
	if (this->cmp == NULL)
		return FALSE;

	struct lvlval_excpt_item *item;
	int rtn;


	list_for_each_entry(item, &(this->excpt_list), node) {
		rtn = this->cmp(item->opaque_data, opaque_data);
		if (rtn) {
			item->caught = TRUE;
			return TRUE;
		}
	}

	return FALSE;
}
