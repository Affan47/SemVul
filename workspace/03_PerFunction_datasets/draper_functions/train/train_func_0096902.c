e_shelf_orient(E_Shelf *es, E_Gadcon_Orient orient)
{
   char buf[4096];

   E_OBJECT_CHECK(es);
   E_OBJECT_IF_NOT_TYPE(es, E_SHELF_DUMMY_TYPE)
     E_OBJECT_TYPE_CHECK(es, E_SHELF_TYPE);

   if (!es->dummy)
     {
        e_gadcon_orient(es->gadcon, orient);
        snprintf(buf, sizeof(buf), "e,state,orientation,%s",
                 e_shelf_orient_string_get(es));
        edje_object_signal_emit(es->o_base, buf, "e");
        edje_object_message_signal_process(es->o_base);
        e_gadcon_location_set_icon_name(es->gadcon->location,
                                        _e_shelf_orient_icon_name_get(es));
     }
   e_zone_useful_geometry_dirty(es->zone);
}
