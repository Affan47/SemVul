_evas_textblock_node_format_new(Evas_Object_Textblock *o, const char *_format)
{
   Evas_Object_Textblock_Node_Format *n;
   const char *format = _format;
   const char *pre_stripped_format = NULL;

   n = calloc(1, sizeof(Evas_Object_Textblock_Node_Format));

   if (format[0] == '<')
     {
        const char *match;
        size_t format_len;
        size_t replace_len;

        format++;
        format_len = strlen(format);
        if ((format_len > 0) && format[format_len - 1] == '>')
          {
             format_len--;

             if ((format_len > 1) && format[format_len - 1] == '/')
               {
                  format_len--;
                  n->own_closer = EINA_TRUE;
               }
          }

        if (!o->style_user || !(match = _style_match_tag(o->style_user, format,
                    format_len, &replace_len)))
          {
             match = _style_match_tag(o->style, format, format_len,
                   &replace_len);
          }

        if (match)
          {
             if (match[0] != '-')
               {
                  n->opener = EINA_TRUE;
                  if (match[0] != '+')
                    {
                       n->own_closer = EINA_TRUE;
                    }
               }

             pre_stripped_format = match;
          }
        else
          {
             if (format[0] == '/')
               {
                  format++;
                  format_len--;
               }
             else
               {
                  n->opener = EINA_TRUE;
               }
          }

        n->orig_format = eina_stringshare_add_length(format, format_len);

        if (!pre_stripped_format)
           pre_stripped_format = n->orig_format;
     }

   else
     {
        const char *tmp = format;
        if (format[0] != '-')
          {
             n->opener = EINA_TRUE;
             if (format[0] != '+')
               {
                  n->own_closer = EINA_TRUE;
               }
          }
        if ((*tmp == '+') || (*tmp == '-'))
          {
             tmp++;
             while (*tmp == ' ') tmp++;
          }
        n->orig_format = eina_stringshare_add(tmp);
        pre_stripped_format = n->orig_format;
     }


     {
        const char *tmp = pre_stripped_format;
        if ((*tmp == '+') || (*tmp == '-'))
          {
             tmp++;
             while (*tmp == ' ') tmp++;
          }
        n->format = eina_stringshare_add(tmp);
     }
   format = n->format;

   _evas_textblock_format_is_visible(n, format);
   if (n->anchor == ANCHOR_A)
     {
        o->anchors_a = eina_list_append(o->anchors_a, n);
     }
   else if (n->anchor == ANCHOR_ITEM)
     {
        o->anchors_item = eina_list_append(o->anchors_item, n);
     }
   n->is_new = EINA_TRUE;

   return n;
}
