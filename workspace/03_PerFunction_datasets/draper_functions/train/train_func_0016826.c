e_color_class_instance_del(E_Color_Class *cc)
{
   Eina_List *n = eina_list_data_find_list(e_config->color_classes, cc);
   if (!n) return;
   e_color_class_node_del(n);
}
