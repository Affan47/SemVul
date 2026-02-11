evas_font_name_parse(Evas_Font_Description *fdesc, const char *name)
{
   const char *end;

   end = strchr(name, ':');
   if (!end)
      eina_stringshare_replace(&(fdesc->name), name);
   else
      eina_stringshare_replace_length(&(fdesc->name), name, end - name);

   while (end)
     {
        const char *tend;
        name = end;
        end = strchr(end + 1, ':');
        if (!end)
           tend = name + strlen(name);
        else
           tend = end;

        if (!strncmp(name, ":style=", 7))
          {
#define _SET_STYLE(x) \
             fdesc->x = _evas_font_style_find_internal(name + 7, tend, \
                   _style_##x##_map, _STYLE_MAP_LEN(_style_##x##_map));
             _SET_STYLE(slant);
             _SET_STYLE(weight);
             _SET_STYLE(width);
#undef _SET_STYLE
          }
        else if (!strncmp(name, ":lang=", 6))
          {
             const char *tmp = name + 6;
             eina_stringshare_replace_length(&(fdesc->lang), tmp, tend - tmp);
          }
     }
}
