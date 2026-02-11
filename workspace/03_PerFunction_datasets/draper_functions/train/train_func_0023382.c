make_sub_express_list(Sub_list *sub_list)
{
    Sub_express *ret;
    Sub_list *tmp_sub_list;
    Boolean flag = TRUE;

    for (tmp_sub_list = sub_list;
         tmp_sub_list != NULL;
         tmp_sub_list = tmp_sub_list->next_dim) {
	Sub_express *sub_exp, *tmp_sub_exp;

	sub_exp = alloc_sub_express();
	sub_exp->sub_script
	    = copy_all_sub_data(tmp_sub_list->sub_id_ptr->sub_script);
	sub_exp->kind
	    = check_kind_of_sub_data(tmp_sub_list->sub_id_ptr->sub_script);
	if (flag) {
	    ret = sub_exp;
	    tmp_sub_exp = ret;
	    flag = FALSE;
	} else {
	    tmp_sub_exp->next_dim = sub_exp;
	    tmp_sub_exp = tmp_sub_exp->next_dim;
	}
    }
    return ret;
}
