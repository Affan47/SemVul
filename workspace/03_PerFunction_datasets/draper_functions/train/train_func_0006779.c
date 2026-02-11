copy_array_subscript_info(Array_subscript_info *source)
{
    Array_subscript_info *ret = NULL;

    if (source) {
	ret = alloc_array_subscript_info();
	ret->entry = source->entry;
	ret->kind = source->kind;
	ret->line_no = source->line_no;
	ret->atm_flg = source->atm_flg;
	ret->block = source->block;
	ret->sub_info = copy_all_sub_list(source->sub_info);
	ret->atm_head = source->atm_head;
	ret->next = source->next;
	ret->next_array = source->next_array;
    }
    return(ret);
}
