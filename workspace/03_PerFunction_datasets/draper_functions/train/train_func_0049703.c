check_most_inner_mt(Block *bpt)
{
    Boolean	flag = FALSE;
    Boolean	flag2 = FALSE;

    if (bpt != NULL) {
	if (bpt->usage == USE_MT) {
	    if (bpt->hmdf == NULL) {
		check_hmdf_inner(bpt->inner, &flag2);
		if (flag2 == FALSE) flag = TRUE;
	    }
	}
    }
    return flag;
}
