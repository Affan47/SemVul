cons_val(const cst_val *a, const cst_val *b)
{
    cst_val *v = new_val();
    CST_VAL_CAR(v)=((!a || cst_val_consp(a)) ?
		    (cst_val *)(void *)a:val_inc_refcount(a));
    CST_VAL_CDR(v)=((!b || cst_val_consp(b)) ?
		    (cst_val *)(void *)b:val_inc_refcount(b));
    return v;
}
