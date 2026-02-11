val_dec_refcount(const cst_val *b)
{
    cst_val *wb;

    wb = (cst_val *)(void *)b;

    if (CST_VAL_REFCOUNT(wb) == -1)

	return -1;
    else if (cst_val_consp(wb))
	return 0;
    else if (CST_VAL_REFCOUNT(wb) == 0)
    {


	return 0;
    }
    else
    {
	CST_VAL_REFCOUNT(wb) -= 1;
	return 	CST_VAL_REFCOUNT(wb);
    }
}
