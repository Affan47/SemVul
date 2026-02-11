gui_cleanup(void)
{
#ifdef ENABLE_PLUGINS
   struct plugin_s *plugin;
   GList *plugin_list, *temp_list;
#endif

#ifdef ENABLE_PLUGINS
   plugin_list = NULL;
   plugin_list = get_plugin_list();


   for (temp_list = plugin_list; temp_list; temp_list = temp_list->next) {
      plugin = (struct plugin_s *)temp_list->data;
      if (plugin) {
         if (plugin->number == glob_app) {
            if (plugin->plugin_gui_cleanup) {
               plugin->plugin_gui_cleanup();
            }
            break;
         }
      }
   }
#endif

   switch (glob_app) {
    case DATEBOOK:
      datebook_gui_cleanup();
      break;
    case ADDRESS:
      address_gui_cleanup();
      break;
    case TODO:
      todo_gui_cleanup();
      break;
    case MEMO:
      memo_gui_cleanup();
      break;
    default:
      break;
   }
   return EXIT_SUCCESS;
}
