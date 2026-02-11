spif_tok_show(spif_tok_t self, spif_charptr_t name, spif_str_t buff, size_t indent)
{
    spif_char_t tmp[4096];

    if (SPIF_TOK_ISNULL(self)) {
        SPIF_OBJ_SHOW_NULL(tok, name, buff, indent, tmp);
        return buff;
    }

    memset(tmp, ' ', indent);
    snprintf(SPIF_CHARPTR_C(tmp) + indent, sizeof(tmp) - indent,
             "(spif_tok_t) %s:  %10p {\n",
             name, SPIF_CAST(ptr) self);
    if (SPIF_STR_ISNULL(buff)) {
        buff = spif_str_new_from_ptr(tmp);
    } else {
        spif_str_append_from_ptr(buff, tmp);
    }
    buff = spif_str_show(SPIF_STR(self->src), SPIF_CHARPTR("src"), buff, indent + 2);
    buff = spif_str_show(SPIF_STR(self->sep), SPIF_CHARPTR("sep"), buff, indent + 2);

    indent += 2;
    memset(tmp, ' ', indent);
    snprintf(SPIF_CHARPTR_C(tmp) + indent, sizeof(tmp) - indent, "(spif_char_t) quote:  '%c' (0x%02x)\n",
             (char) self->quote, (unsigned int) self->quote);
    spif_str_append_from_ptr(buff, tmp);
    snprintf(SPIF_CHARPTR_C(tmp) + indent, sizeof(tmp) - indent, "(spif_char_t) dquote:  '%c' (0x%02x)\n",
             (char) self->dquote, (unsigned int) self->dquote);
    spif_str_append_from_ptr(buff, tmp);
    snprintf(SPIF_CHARPTR_C(tmp) + indent, sizeof(tmp) - indent, "(spif_char_t) escape:  '%c' (0x%02x)\n",
             (char) self->escape, (unsigned int) self->escape);
    spif_str_append_from_ptr(buff, tmp);

    SPIF_LIST_SHOW(self->tokens, buff, indent);
    indent -= 2;

    snprintf(SPIF_CHARPTR_C(tmp) + indent, sizeof(tmp) - indent, "}\n");
    spif_str_append_from_ptr(buff, tmp);
    return buff;
}
