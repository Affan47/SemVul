delete_config()
{
   config_entry *next;

   while (config_list) {
      next = config_list->next;
      if (config_list->name)
         free(config_list->name);
      if (config_list->value)
         free(config_list->value);
      free(config_list);
      config_list = next;
   }
}
