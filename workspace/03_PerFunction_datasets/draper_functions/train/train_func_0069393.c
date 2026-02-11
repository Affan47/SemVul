delete_val(cst_val *v)
{
    if (v)
    {
	if (cst_val_consp(v))
	{
	    delete_val(CST_VAL_CAR(v));
	    delete_val(CST_VAL_CDR(v));
	    cst_free(v);
	}
	else if (val_dec_refcount(v) == 0)
	{
	    if (CST_VAL_TYPE(v) == CST_VAL_TYPE_STRING)
		cst_free(CST_VAL_VOID(v));
	    else if (CST_VAL_TYPE(v) >= CST_VAL_TYPE_FIRST_FREE)
            {
                if (cst_val_defs[CST_VAL_TYPE(v)/2].delete_function)
                    (cst_val_defs[CST_VAL_TYPE(v)/2].delete_function)
                        (CST_VAL_VOID(v));
            }
            cst_free(v);
	}
    }
}
