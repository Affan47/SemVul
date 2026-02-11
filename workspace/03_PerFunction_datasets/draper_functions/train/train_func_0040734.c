helper_attach_driver(UPSINFO *ups, const char *drvname)
{
   int i;

   write_lock(ups);

   Dmsg1(99, "Looking for driver: %s\n", drvname);
   ups->driver = NULL;

   for (i = 0; drivers[i].driver_name; i++) {
      Dmsg1(99, "Driver %s is configured.\n", drivers[i].driver_name);
      if (strcasecmp(drivers[i].driver_name, drvname) == 0) {
         ups->driver = &drivers[i];
         Dmsg1(20, "Driver %s found and attached.\n", drivers[i].driver_name);
         break;
      }
   }

   if (!ups->driver) {
      printf("\nApcupsd driver %s not found.\n"
             "The available apcupsd drivers are:\n", drvname);

      for (i = 0; drivers[i].driver_name; i++)
         printf("%s\n", drivers[i].driver_name);

      printf("\n");
      printf("Most likely, you need to add --enable-%s "
             "to your ./configure options.\n\n", drvname);
   }

   write_unlock(ups);

   Dmsg1(99, "Driver ptr=0x%x\n", ups->driver);
   return ups->driver;
}
