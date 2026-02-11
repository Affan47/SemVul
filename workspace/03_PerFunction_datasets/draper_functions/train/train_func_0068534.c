e_color_class_node_del(Eina_List *n)
{
   E_Color_Class *cc = n->data;
   edje_color_class_del(cc->name);
   eina_stringshare_del(cc->name);
   E_FREE(cc);

   e_config->color_classes = eina_list_remove_list(e_config->color_classes, n);
   e_config_save_queue();
}
