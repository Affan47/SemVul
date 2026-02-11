set_obj_value(node *obj,node *value)
{
  node *kv = node_GetItemByKey(obj,"value");
  if(kv==NULL)
    add_obj_kv(obj,value);
  else
  {
    remove_obj_kv(obj,kv);
    node_FreeTree(kv);
    add_obj_kv(obj,value);
  }
}
