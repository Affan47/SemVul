str_cat(STR *str, const char *ptr)
{
    int len;

    if (!ptr)
	return;
    if (!(str->str_pok))
	str_2ptr(str);
    len = strlen(ptr);
    GROWSTR(&(str->str_ptr), &(str->str_len), str->str_cur + len + 1);
    memcpy(str->str_ptr+str->str_cur, ptr, len+1);
    str->str_cur += len;
    str->str_nok = 0;
    str->str_pok = 1;
}
