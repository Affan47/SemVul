spif_objpair_show(spif_objpair_t self, spif_charptr_t name, spif_str_t buff, size_t indent)
{
    spif_char_t tmp[4096];

    if (SPIF_OBJPAIR_ISNULL(self)) {
        SPIF_OBJ_SHOW_NULL(objpair, name, buff, indent, tmp);
        return buff;
    }

    memset(tmp, ' ', indent);
    snprintf(SPIF_CAST_C(char *) tmp + indent, sizeof(tmp) - indent,
             "(spif_objpair_t) %s:  %10p \"%s\"\n",
             name, SPIF_CAST(ptr) self, SPIF_OBJ_CLASSNAME(self));
    if (SPIF_STR_ISNULL(buff)) {
        buff = spif_str_new_from_ptr(tmp);
    } else {
        spif_str_append_from_ptr(buff, tmp);
    }
    return buff;
}
