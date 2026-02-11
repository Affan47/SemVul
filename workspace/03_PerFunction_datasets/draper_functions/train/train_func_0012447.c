dri3_create_display(Display * dpy)
{
   struct dri3_display                  *pdp;
   int                                  i;
   xcb_connection_t                     *c = XGetXCBConnection(dpy);
   xcb_dri3_query_version_cookie_t      dri3_cookie;
   xcb_dri3_query_version_reply_t       *dri3_reply;
   xcb_present_query_version_cookie_t   present_cookie;
   xcb_present_query_version_reply_t    *present_reply;
   xcb_generic_error_t                  *error;
   const xcb_query_extension_reply_t    *extension;

   xcb_prefetch_extension_data(c, &xcb_dri3_id);
   xcb_prefetch_extension_data(c, &xcb_present_id);

   extension = xcb_get_extension_data(c, &xcb_dri3_id);
   if (!(extension && extension->present))
      return NULL;

   extension = xcb_get_extension_data(c, &xcb_present_id);
   if (!(extension && extension->present))
      return NULL;

   dri3_cookie = xcb_dri3_query_version(c,
                                        XCB_DRI3_MAJOR_VERSION,
                                        XCB_DRI3_MINOR_VERSION);


   present_cookie = xcb_present_query_version(c,
                                   XCB_PRESENT_MAJOR_VERSION,
                                   XCB_PRESENT_MINOR_VERSION);

   pdp = malloc(sizeof *pdp);
   if (pdp == NULL)
      return NULL;

   dri3_reply = xcb_dri3_query_version_reply(c, dri3_cookie, &error);
   if (!dri3_reply) {
      free(error);
      goto no_extension;
   }

   pdp->dri3Major = dri3_reply->major_version;
   pdp->dri3Minor = dri3_reply->minor_version;
   free(dri3_reply);

   present_reply = xcb_present_query_version_reply(c, present_cookie, &error);
   if (!present_reply) {
      free(error);
      goto no_extension;
   }
   pdp->presentMajor = present_reply->major_version;
   pdp->presentMinor = present_reply->minor_version;
   free(present_reply);

   pdp->base.destroyDisplay = dri3_destroy_display;
   pdp->base.createScreen = dri3_create_screen;

   loader_set_logger(dri_message);
   i = 0;

   pdp->loader_extensions[i++] = &imageLoaderExtension.base;

   pdp->loader_extensions[i++] = &systemTimeExtension.base;

   pdp->loader_extensions[i++] = NULL;

   return &pdp->base;
no_extension:
   free(pdp);
   return NULL;
}
