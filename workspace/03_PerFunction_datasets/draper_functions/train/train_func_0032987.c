bdf_get_font_property(bdf_font_t *font, const char *name)
#else
bdf_get_font_property(font, name)
bdf_font_t *font;
const char *name;
#endif
{
    hashnode hn;

    if (font == 0 || font->props_size == 0 || name == 0 || *name == 0)
      return 0;

    hn = hash_lookup((char*)name, (hashtable *) font->internal);
    return (hn) ? (font->props + ((unsigned long) hn->data)) : 0;
}
