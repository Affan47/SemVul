bdf_set_modified(bdf_font_t *font, int modified)
#else
bdf_set_modified(font, modified)
bdf_font_t *font;
int modified;
#endif
{
    if (font == 0 || font->modified == modified)
      return;

    if (modified == 0) {


        (void) memset((char *) font->nmod, 0, sizeof(unsigned long) * 2048);
        (void) memset((char *) font->umod, 0, sizeof(unsigned long) * 2048);
    }
    font->modified = modified;
}
