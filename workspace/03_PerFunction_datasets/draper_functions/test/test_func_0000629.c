e_msgbus_shutdown(void)
{
   if (_e_msgbus_data->obj)
     {
        e_dbus_object_free(_e_msgbus_data->obj);
     }
   if (_e_msgbus_data->conn)
     {
        e_dbus_connection_close(_e_msgbus_data->conn);
     }
#ifdef HAVE_HAL
   e_hal_shutdown();
#endif
   e_dbus_shutdown();

   E_FREE(_e_msgbus_data);
   _e_msgbus_data = NULL;
   return 1;
}
