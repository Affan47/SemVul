sb_string_dup(sb_string_t *str)
{
    if (str == NULL)
        return NULL;
    sb_string_t* new = sb_string_new();
    return sb_string_append_len(new, str->str, str->len);
}
