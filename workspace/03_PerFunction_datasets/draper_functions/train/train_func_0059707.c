str_set(STR *str, const char *ptr)
{
    int len;

    if (!ptr)
	ptr = "";
    len = strlen(ptr);
    GROWSTR(&(str->str_ptr), &(str->str_len), len + 1);
    memcpy(str->str_ptr,ptr,len+1);
    str->str_cur = len;
    str->str_nok = 0;
    str->str_pok = 1;
}
