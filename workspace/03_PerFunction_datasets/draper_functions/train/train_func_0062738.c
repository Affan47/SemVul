setup_im(XIM_Im_Info *info)
{
   XIMValuesList *ic_values = NULL;
   XIMCallback im_destroy_callback;

   if (!info->im)
     return;

   im_destroy_callback.client_data = (XPointer)info;
   im_destroy_callback.callback = (XIMProc)xim_destroy_callback;
   XSetIMValues(info->im,
                XNDestroyCallback, &im_destroy_callback,
                NULL);

   XGetIMValues(info->im,
                XNQueryInputStyle, &info->xim_styles,
                XNQueryICValuesList, &ic_values,
                NULL);

   if (ic_values)
     {
        int i;

        for (i = 0; i < ic_values->count_values; i++)
          {
             if (!strcmp(ic_values->supported_values[i],
                         XNStringConversionCallback))
               info->supports_string_conversion = EINA_TRUE;
             if (!strcmp(ic_values->supported_values[i],
                         XNCursor))
               info->supports_cursor = EINA_TRUE;
          }
#if 0
        printf("values........\n");
        for (i = 0; i < ic_values->count_values; i++)
          printf("%s\n", ic_values->supported_values[i]);
        printf("styles........\n");
        for (i = 0; i < info->xim_styles->count_styles; i++)
          printf("%lx\n", info->xim_styles->supported_styles[i]);
#endif
        XFree(ic_values);
     }
}
