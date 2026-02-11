glXGetDriverConfig(const char *driverName)
{
   void *handle = driOpenDriver(driverName);
   const __DRIextension **extensions;

   if (!handle)
      return NULL;

   extensions = driGetDriverExtensions(handle, driverName);
   if (extensions) {
      for (int i = 0; extensions[i]; i++) {
         if (strcmp(extensions[i]->name, __DRI_CONFIG_OPTIONS) == 0)
            return ((__DRIconfigOptionsExtension *)extensions[i])->xml;
      }
   }


   return dlsym(handle, "__driConfigOptions");
}
