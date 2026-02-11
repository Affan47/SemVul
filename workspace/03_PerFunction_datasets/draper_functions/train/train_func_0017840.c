e_smart_monitor_clone_add(Evas_Object *obj, Evas_Object *mon)
{
   E_Smart_Data *osd, *msd;
   Evas_Object *o;
   Evas_Coord mw = 0, mh = 0;


   if (!(osd = evas_object_smart_data_get(obj))) return;


   if (!(msd = evas_object_smart_data_get(mon))) return;


   msd->current.cloned = EINA_TRUE;


   if (msd->orig.cloned != msd->current.cloned)
     msd->changes |= E_SMART_MONITOR_CHANGED_CLONED;
   else
     msd->changes &= ~(E_SMART_MONITOR_CHANGED_CLONED);


   msd->parent = obj;


   evas_object_geometry_get(msd->o_frame, NULL, NULL, &mw, &mh);


   if (msd->visible) evas_object_hide(mon);


   mw *= 0.25;
   mh *= 0.25;


   msd->o_clone = edje_object_add(osd->evas);
   e_theme_edje_object_set(msd->o_clone, "base/theme/widgets",
                           "e/conf/randr/main/mini");

   evas_object_data_set(msd->o_clone, "smart_data", msd);

   edje_object_part_unswallow(msd->o_frame, msd->o_thumb);
   evas_object_hide(msd->o_thumb);


   edje_object_part_swallow(msd->o_clone, "e.swallow.preview", msd->o_thumb);
   evas_object_show(msd->o_thumb);

   if ((msd->current.orientation == ECORE_X_RANDR_ORIENTATION_ROT_0) ||
       (msd->current.orientation == ECORE_X_RANDR_ORIENTATION_ROT_180))
     {

        evas_object_size_hint_min_set(msd->o_clone, mw, mh);
     }
   else
     {

        evas_object_size_hint_min_set(msd->o_clone, mh, mw);
     }


   evas_object_resize(msd->o_clone, mw, mh);


   evas_object_show(msd->o_clone);


   osd->clones = eina_list_append(osd->clones, msd->o_clone);


   edje_object_part_box_append(osd->o_frame, "e.box.clone", msd->o_clone);


   if ((o = (Evas_Object *)
        edje_object_part_object_get(osd->o_frame, "e.box.clone")))
     {
        evas_object_size_hint_min_get(o, &mw, &mh);
        if (mw < 1) mw = 1;
        if (mh < 1) mh = 1;
        evas_object_resize(o, mw, mh);
     }


   _e_smart_monitor_map_apply(msd->o_clone, msd->current.rotation);


   evas_object_smart_callback_call(mon, "monitor_changed", NULL);
}
