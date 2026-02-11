_e_wid_cb_scrollframe_resize(void *data, Evas *e __UNUSED__, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Coord mw, mh, vw, vh, w, h;

   e_scrollframe_child_viewport_size_get(obj, &vw, &vh);
   e_ilist_size_min_get(data, &mw, &mh);
   evas_object_geometry_get(data, NULL, NULL, &w, &h);
   if (vw >= mw)
     {
        if (w != vw) evas_object_resize(data, vw, h);
        evas_object_smart_callback_call(data, "changed", obj);
     }
}
