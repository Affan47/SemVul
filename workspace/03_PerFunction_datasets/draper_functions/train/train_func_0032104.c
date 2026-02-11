last_accent(const cst_item *syl)
{
    const cst_item *s;
    int c;

    for (c=0,s=item_as(syl,"Syllable");
	 s && (c < CST_CONST_INT_MAX);
	 s=item_prev(s),c++)
    {
	if (val_int(accented(s)))
	    return val_string_n(c);
    }

    return val_string_n(c);
}
