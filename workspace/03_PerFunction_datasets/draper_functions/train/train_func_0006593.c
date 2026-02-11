create(THD *thd, LEX_STRING db, LEX_STRING name,
                       bool use_explicit_name, List<Item> *item_list)
{
  int arg_count= 0;
  Item *func= NULL;
  LEX *lex= thd->lex;
  sp_name *qname;

  if (has_named_parameters(item_list))
  {


    my_error(ER_WRONG_PARAMETERS_TO_STORED_FCT, MYF(0), name.str);
    return NULL;
  }

  if (item_list != NULL)
    arg_count= item_list->elements;

  qname= new (thd->mem_root) sp_name(db, name, use_explicit_name);
  qname->init_qname(thd);
  sp_add_used_routine(lex, thd, qname, TYPE_ENUM_FUNCTION);

  if (arg_count > 0)
    func= new (thd->mem_root) Item_func_sp(lex->current_context(), qname,
                                           *item_list);
  else
    func= new (thd->mem_root) Item_func_sp(lex->current_context(), qname);

  lex->safe_to_cache_query= 0;
  return func;
}
