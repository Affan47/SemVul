nyxh_div(node *state,node *self,node *obj,node *block,node *parameters)
{
  node *value = copy_class(obj);
  add_garbage(state,value);
  node *value2 = node_GetItem(parameters,0);
  node *real_value = get_value(value);
  node *real_value2 = get_value(value2);

  if(node_GetType(real_value)==NODE_TYPE_DOUBLE)
  {
    double d1,d2;
    d1=node_GetDouble(real_value);
    if(node_GetType(real_value2)==NODE_TYPE_DOUBLE)
      d2=node_GetDouble(real_value2);
    else if(node_GetType(real_value2)==NODE_TYPE_SINT32)
      d2=(double)node_GetSint32(real_value2);
    else if(node_GetType(real_value2)==NODE_TYPE_STRING)
      d2=(double)atof(node_GetString(real_value2));
    set_obj_float(value,"value",d1/d2);
  }
  else if(node_GetType(real_value)==NODE_TYPE_SINT32)
  {
    long l1,l2;
    l1=node_GetSint32(real_value);
    if(node_GetType(real_value2)==NODE_TYPE_DOUBLE)
      l2=(long)node_GetDouble(real_value2);
    else if(node_GetType(real_value2)==NODE_TYPE_SINT32)
      l2=node_GetSint32(real_value2);
    else if(node_GetType(real_value2)==NODE_TYPE_STRING)
      l2=atol(node_GetString(real_value2));
    set_obj_int(value,"value",l1/l2);
  }
  else if(node_GetType(real_value)==NODE_TYPE_STRING)
  {
    if(node_GetType(real_value2)==NODE_TYPE_DOUBLE)
    {
      set_obj_float(value,"value",atof(node_GetString(real_value))/node_GetSint32(real_value2));
    }
    else if(node_GetType(real_value2)==NODE_TYPE_SINT32)
    {
      set_obj_int(value,"value",atol(node_GetString(real_value))/node_GetSint32(real_value2));
    }
    else if(node_GetType(real_value2)==NODE_TYPE_STRING)
      set_obj_int(value,"value",0);
  }
  return(value);
}
