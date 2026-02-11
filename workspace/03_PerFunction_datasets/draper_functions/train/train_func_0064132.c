MetaphAdd(metastring * s, char *new_str)
{
    int add_length;

    if (new_str == NULL)
	    return;

    add_length = strlen(new_str);
    if ((s->length + add_length) > (s->bufsize - 1))
	    IncreaseBuffer(s, add_length);

    strcat(s->str, new_str);
    s->length += add_length;
}
