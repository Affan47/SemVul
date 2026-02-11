_elm_tooltip_data_clean(Elm_Tooltip *tt)
{
   if (tt->del_cb) tt->del_cb((void *)tt->data, tt->owner, NULL);

   _elm_tooltip_content_del(tt);

   tt->data = NULL;
   tt->del_cb = NULL;
}
