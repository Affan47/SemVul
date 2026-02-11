ecore_evas_ews_setup(int x, int y, int w, int h)
{
#ifdef BUILD_ECORE_EVAS_EWS
   Eina_Bool ret = EINA_TRUE;

   _ews_defaults_geo = EINA_FALSE;
   _ews_x = x;
   _ews_y = y;
   _ews_w = w;
   _ews_h = h;

   if (!_ews_ee) return EINA_TRUE;


   ecore_evas_move(_ews_ee, x, y);
   ecore_evas_size_min_set(_ews_ee, w, h);
   ecore_evas_size_max_set(_ews_ee, w, h);
   ecore_evas_resize(_ews_ee, w, h);

   ecore_evas_geometry_get(_ews_ee, &x, &y, &w, &h);

#define TST(n) if ((n != _ews_##n))                     \
     {                                                  \
        WRN("Asked %d, got %d for "#n, _ews_##n, n);    \
        ret = EINA_FALSE;                               \
     }
   TST(x);
   TST(y);
   TST(w);
   TST(h);
#undef TST
   return ret;
#else
   return EINA_FALSE;
   (void)x;
   (void)y;
   (void)w;
   (void)h;
#endif
}
