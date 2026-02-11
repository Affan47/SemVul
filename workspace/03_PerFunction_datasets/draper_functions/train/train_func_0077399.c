following_slash(string_ty *s, size_t len)
{
    for (;;)
    {
	if (s->str_length <= len)
	    return str_copy(s);
	if (s->str_text[len] == '/')
	    return str_n_from_c(s->str_text, len + 1);
	++len;
    }
}
