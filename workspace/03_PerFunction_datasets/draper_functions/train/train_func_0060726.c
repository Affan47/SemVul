_elm_layout_part_aliasing_eval(Elm_Layout_Smart_Data *sd,
                               const char **part,
                               Eina_Bool is_text)
{
#define ALIAS_LIST(_sd, _list) \
  ((ELM_LAYOUT_CLASS(ELM_WIDGET_DATA(_sd)->api))->_list)

   const Elm_Layout_Part_Alias_Description *aliases = is_text ?
     ALIAS_LIST(sd, text_aliases) : ALIAS_LIST(sd, content_aliases);

#undef ALIAS_LIST

   while (aliases && aliases->alias && aliases->real_part)
     {

        if ((!*part) || (!strcmp(*part, aliases->alias)))
          {
             *part = aliases->real_part;
             break;
          }

        aliases++;
     }

   if (!*part)
     {
        ERR("no default content part set for object %p -- "
            "part must not be NULL", ELM_WIDGET_DATA(sd)->obj);
        return EINA_FALSE;
     }


   return EINA_TRUE;
}
