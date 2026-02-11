elm_object_cnp_selection_clear(Evas_Object *obj, Elm_Sel_Type selection)
{
   if (selection > ELM_SEL_TYPE_CLIPBOARD) return EINA_FALSE;
   if (!_elm_cnp_init_count) _elm_cnp_init();
#ifdef HAVE_ELEMENTARY_X
   if (_x11_elm_widget_xwin_get(obj))
     return _x11_elm_object_cnp_selection_clear(obj, selection);
#endif
   return _local_elm_object_cnp_selection_clear(obj, selection);
}
