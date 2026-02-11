nyxh_cmp(node *state,node *self,node *obj,node *block,node *parameters)
{


  node *value = NULL;

  node *expression_block = node_GetItem(parameters,0);
  node *true_block = node_GetItem(parameters,1);
  node *false_block = node_GetItem(parameters,2);
  node *loop_exe = node_GetItem(parameters,3);

  inc_obj_refcount(expression_block);
  inc_obj_refcount(true_block);
  inc_obj_refcount(false_block);

  node *loop = execute_obj(state,loop_exe,block,NULL,True,False,True);
  node *loop_value = get_value(loop);
  long lv = node_GetSint32(loop_value);


  if(lv)
  {
    node *exp_obj = execute_obj(state,expression_block,block,NULL,True,False,True);

    while(node_GetSint32(get_value(exp_obj)))
    {
      execute_obj(state,true_block,block,NULL,True,False,True);
      char *block_flag=check_block_flag(state);
      if(block_flag)
      {
        if(!strcmp(block_flag,"break")||!strcmp(block_flag,"exit")||!strcmp(block_flag,"return"))
          break;
        free(block_flag);
      }
      exp_obj = execute_obj(state,expression_block,block,NULL,True,False,True);
    }
    execute_obj(state,false_block,block,NULL,True,False,True);
    value = get_true_class(state);
  }
  else
  {
    node *exp_val=execute_obj(state,expression_block,block,NULL,True,False,True);

    if(node_GetSint32(get_value(exp_val)))
      value = get_true_class(state);
    else
      value = get_false_class(state);

    if(node_GetSint32(get_value(exp_val)))
    {
      execute_obj(state,true_block,block,NULL,True,False,True);
    }
    else
      execute_obj(state,false_block,block,NULL,True,False,True);
  }

  dec_obj_refcount(expression_block);
  dec_obj_refcount(true_block);
  dec_obj_refcount(false_block);
  add_garbage(state,expression_block);
  add_garbage(state,true_block);
  add_garbage(state,false_block);
  return(value);
}
