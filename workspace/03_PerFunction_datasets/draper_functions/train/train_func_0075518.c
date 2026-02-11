intelCreateContext(gl_api api,
		   const struct gl_config * mesaVis,
                   __DRIcontext * driContextPriv,
		   unsigned major_version,
		   unsigned minor_version,
		   uint32_t flags,
                   bool notify_reset,
		   unsigned *error,
                   void *sharedContextPrivate)
{
   bool success = false;

   __DRIscreen *sPriv = driContextPriv->driScreenPriv;
   struct intel_screen *intelScreen = sPriv->driverPrivate;

   if (flags & ~__DRI_CTX_FLAG_DEBUG) {
      *error = __DRI_CTX_ERROR_UNKNOWN_FLAG;
      return false;
   }

   if (notify_reset) {
      *error = __DRI_CTX_ERROR_UNKNOWN_ATTRIBUTE;
      return false;
   }

   if (IS_9XX(intelScreen->deviceID)) {
      success = i915CreateContext(api, mesaVis, driContextPriv,
                                  major_version, minor_version, flags,
                                  error, sharedContextPrivate);
   } else {
      intelScreen->no_vbo = true;
      success = i830CreateContext(api, mesaVis, driContextPriv,
                                  major_version, minor_version, flags,
                                  error, sharedContextPrivate);
   }

   if (success)
      return true;

   if (driContextPriv->driverPrivate != NULL)
      intelDestroyContext(driContextPriv);

   return false;
}
