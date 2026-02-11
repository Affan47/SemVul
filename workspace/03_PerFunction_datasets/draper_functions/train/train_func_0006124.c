_pager_window_cb_drag_convert(E_Drag *drag, const char *type)
{
   Pager_Win *pw;

   pw = drag->data;
   if (!strcmp(type, "enlightenment/pager_win")) return pw;
   if (!strcmp(type, "enlightenment/border")) return pw->border;
   return NULL;
}
