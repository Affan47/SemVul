member_nocase(string_ty *s)
    const
{
    for (size_t j = 0; j < nstrings; j++)
	if (0 == strcasecmp(string[j]->str_text, s->str_text))
	    return true;
    return false;
}
