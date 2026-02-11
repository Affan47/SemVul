_elm_ews_wm_rescale(Elm_Theme *th, Eina_Bool use_theme)
{
   Eina_Iterator *it;
   Eina_Hash_Tuple *tp = NULL;

   if (!_ews_borders) return;
   it = eina_hash_iterator_tuple_new(_ews_borders);
   if (!use_theme)
     {
        EINA_ITERATOR_FOREACH(it, tp)
          _elm_ews_wm_border_theme_set(*(void**)tp->key, tp->data, NULL);

        if (_ews_bg)
          _elm_theme_set(NULL, _ews_bg, "ews", "background", "default");
     }
   else
     {
        EINA_ITERATOR_FOREACH(it, tp)
          _elm_ews_wm_border_theme_set(*(void**)tp->key, tp->data, th);

        if (_ews_bg)
          _elm_theme_set(th, _ews_bg, "ews", "background", "default");
     }

   eina_iterator_free(it);
}
