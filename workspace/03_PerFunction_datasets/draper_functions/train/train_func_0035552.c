clear_tv(varp)
    typval_T *varp;
{
    if (varp != NULL)
    {
	switch (varp->v_type)
	{
	    case VAR_FUNC:
		func_unref(varp->vval.v_string);

	    case VAR_STRING:
		vim_free(varp->vval.v_string);
		varp->vval.v_string = NULL;
		break;
	    case VAR_LIST:
		list_unref(varp->vval.v_list);
		varp->vval.v_list = NULL;
		break;
	    case VAR_DICT:
		dict_unref(varp->vval.v_dict);
		varp->vval.v_dict = NULL;
		break;
	    case VAR_NUMBER:
		varp->vval.v_number = 0;
		break;
#ifdef FEAT_FLOAT
	    case VAR_FLOAT:
		varp->vval.v_float = 0.0;
		break;
#endif
	    case VAR_UNKNOWN:
		break;
	    default:
		EMSG2(_(e_intern2), "clear_tv()");
	}
	varp->v_lock = 0;
    }
}
