hp_attach_matching_devices (HpDeviceConfig *config, const char *devname)
{
 static int usb_initialized = 0;

 if (strncmp (devname, "usb", 3) == 0)
 {
   config->connect = HP_CONNECT_USB;
   config->use_scsi_request = 0;
   DBG(1,"hp_attach_matching_devices: usb attach matching \"%s\"\n",devname);
   if (!usb_initialized)
   {
      sanei_usb_init ();
      usb_initialized = 1;
   }
   sanei_usb_attach_matching_devices (devname, hp_attach);
 }
 else
 {
   DBG(1, "hp_attach_matching_devices: attach matching %s\n", devname);
   sanei_config_attach_matching_devices (devname, hp_attach);
 }
}
