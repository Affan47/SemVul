_bdf_add_acmsg(bdf_font_t *font, char *msg, unsigned long len)
#else
_bdf_add_acmsg(font, msg, len)
bdf_font_t *font;
char *msg;
unsigned long len;
#endif
{
    char *cp;

    if (font->acmsgs_len == 0)
      font->acmsgs = (char *) malloc(len + 1);
    else
      font->acmsgs = (char *) realloc(font->acmsgs,
                                      font->acmsgs_len + len + 1);

    cp = font->acmsgs + font->acmsgs_len;
    (void) memcpy(cp, msg, len);
    cp += len;
    *cp++ = '\n';
    font->acmsgs_len += len + 1;
}
