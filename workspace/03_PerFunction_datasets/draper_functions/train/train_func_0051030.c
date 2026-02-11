e_xsettings_shutdown(void)
{
   _e_xsettings_stop();
   if (eio_op) eio_file_cancel(eio_op);
   eio_op = NULL;
   setting = EINA_FALSE;
   event_ignore = 0;

   return 1;
}
