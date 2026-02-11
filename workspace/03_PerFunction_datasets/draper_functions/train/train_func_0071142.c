nyx_add_parameter(node *state,char *parameter)
{
  #ifdef USE_SYS
  node *nyx_stream = nyx_LoadString(parameter);
  if(nyx_stream!=NULL)
  {
    node *nyx_block = node_GetItemByKey(nyx_stream,"nyx_block");
    if(nyx_block!=NULL)
    {
      add_obj_kv(state,nyx_block);
      node_RemoveItem(nyx_stream,nyx_block);
      node_FreeTree(nyx_stream);
      node *ret_obj = evaluate_block(state,nyx_block);
      node_RemoveItem(state,nyx_block);
      sys_add_parameter(state,ret_obj);
      node_FreeTree(nyx_block);
    }
  }
  #endif
}
