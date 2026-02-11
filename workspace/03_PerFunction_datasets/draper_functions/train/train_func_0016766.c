ojc_create_number(const char *num, size_t len) {
    ojcVal	val = _ojc_val_create(OJC_NUMBER);

    if (0 >= len) {
	len = strlen(num);
    }
    if (sizeof(union _Bstr) <= len) {
	val->str_type = STR_PTR;
	val->str.str = strndup(num, len);
	val->str.str[len] = '\0';
    } else if (sizeof(val->str.ca) <= len) {
	val->str_type = STR_BLOCK;
	val->str.bstr = _ojc_bstr_create();
	memcpy(val->str.bstr->ca, num, len);
	val->str.bstr->ca[len] = '\0';
    } else {
	val->str_type = STR_ARRAY;
	memcpy(val->str.ca, num, len);
	val->str.ca[len] = '\0';
    }
    return val;
}
