en_exp_real(const char *numstring)
{
    char *aaa, *p;
    cst_val *r;

    if (numstring && (numstring[0] == '-'))
	r = cons_val(string_val("minus"),
		     en_exp_real(&numstring[1]));
    else if (numstring && (numstring[0] == '+'))
	r = cons_val(string_val("plus"),
		     en_exp_real(&numstring[1]));
    else if (((p=strchr(numstring,'e')) != 0) ||
	     ((p=strchr(numstring,'E')) != 0))
    {
	aaa = cst_strdup(numstring);
	aaa[cst_strlen(numstring)-cst_strlen(p)] = '\0';
	r = val_append(en_exp_real(aaa),
		       cons_val(string_val("e"),
				en_exp_real(p+1)));
	cst_free(aaa);
    }
    else if ((p=strchr(numstring,'.')) != 0)
    {
	aaa = cst_strdup(numstring);
	aaa[cst_strlen(numstring)-cst_strlen(p)] = '\0';
	r = val_append(en_exp_number(aaa),
		       cons_val(string_val("point"),
				en_exp_digits(p+1)));
	cst_free(aaa);
    }
    else
	r = en_exp_number(numstring);

    return r;
}
