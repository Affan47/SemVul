usb_ups_get_capabilities(UPSINFO *ups)
{
   int rc;


   rc = pusb_ups_get_capabilities(ups, known_info);
   if (!rc)
      return 0;


   if (ups->UPS_Cap[CI_Discharging])
      ups->UPS_Cap[CI_ACPresent] = false;


   USB_VALUE uval;
   if (ups->UPS_Cap[CI_NOMPOWER] &&
       (!usb_get_value(ups, CI_NOMPOWER, &uval) ||
        ((int)uval.dValue == 0))) {
      Dmsg0(100, "NOMPOWER disabled due to invalid reading from UPS\n");
      ups->UPS_Cap[CI_NOMPOWER] = false;
   }


   quirk_old_backups_pro = false;
   if (ups->UPS_Cap[CI_UPSMODEL] && usb_get_value(ups, CI_UPSMODEL, &uval)) {
      Dmsg1(250, "Checking for BackUPS Pro quirk \"%s\"\n", uval.sValue);
      if (!strcmp(uval.sValue, QUIRK_OLD_BACKUPS_PRO_MODEL_STRING)) {
         quirk_old_backups_pro = true;
         Dmsg0(100, "BackUPS Pro quirk enabled\n");
      }
   }

   return 1;
}
