Stringstriptrail(String *str)
{
    while (is_space(str->data[str->len - 1]))
	--str->len;
    str->data[str->len] = '\0';
    return str;
}
