HULnext_node(list_head_t *lst
)
{
    CONSTR(FUNC, "HULnext_node");
    VOIDP ret_value=NULL;

    HEclear();
    if(lst==NULL)
        HGOTO_ERROR(DFE_ARGS,NULL);

    if(lst->curr_node!=NULL)
      {
        lst->curr_node=lst->curr_node->next;
        if(lst->curr_node!=NULL)
            HGOTO_DONE(lst->curr_node->obj_ptr);
      }

done:
  if(ret_value == NULL)
    {

    }


  return ret_value;
}
