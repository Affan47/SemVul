cb_desktop_bgdel(E_DBus_Object *obj __UNUSED__, DBusMessage *msg)
{
   DBusError err;
   int container, zone, desk_x, desk_y;

   dbus_error_init(&err);
   if (!dbus_message_get_args(msg, &err,
			      DBUS_TYPE_INT32, &container,
			      DBUS_TYPE_INT32, &zone,
			      DBUS_TYPE_INT32, &desk_x,
			      DBUS_TYPE_INT32, &desk_y,
			      DBUS_TYPE_INVALID))
     {
	ERR("could not get Del arguments: %s: %s", err.name, err.message);
	dbus_error_free(&err);
     }
   else
     {
	DBG("del bg container=%d, zone=%d, pos=%d,%d",
	    container, zone, desk_x, desk_y);

	e_bg_del(container, zone, desk_x, desk_y);
	e_bg_update();
	e_config_save_queue();
     }

   return dbus_message_new_method_return(msg);
}
