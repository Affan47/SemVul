country_validate(
	struct berval *val
)
{
	int     rc = 0;


	if (val != NULL) {
		if ((val->bv_len != 2) || !IS_PRINTABLE(val->bv_val[0]) || !IS_PRINTABLE(val->bv_val[1])) {
			rc = 1;
			goto exit;
		}


	} else {
		rc = 1;
	}

exit:
	return(rc);
}
