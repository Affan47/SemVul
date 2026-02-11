elm_gengrid_item_tooltip_text_set(Elm_Object_Item *it,
                                  const char *text)
{
   ELM_GENGRID_ITEM_CHECK_OR_RETURN(it);

   text = eina_stringshare_add(text);
   elm_gengrid_item_tooltip_content_cb_set
     (it, _elm_gengrid_item_label_create, text,
     _elm_gengrid_item_label_del_cb);
}
