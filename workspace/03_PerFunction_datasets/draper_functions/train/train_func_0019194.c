insert(SEL_ARG *key)
{
  SEL_ARG *element,**UNINIT_VAR(par),*UNINIT_VAR(last_element);

  for (element= this; element != &null_element ; )
  {
    last_element=element;
    if (key->cmp_min_to_min(element) > 0)
    {
      par= &element->right; element= element->right;
    }
    else
    {
      par = &element->left; element= element->left;
    }
  }
  *par=key;
  key->parent=last_element;

  if (par == &last_element->left)
  {
    key->next=last_element;
    if ((key->prev=last_element->prev))
      key->prev->next=key;
    last_element->prev=key;
  }
  else
  {
    if ((key->next=last_element->next))
      key->next->prev=key;
    key->prev=last_element;
    last_element->next=key;
  }
  key->left=key->right= &null_element;
  SEL_ARG *root=rb_insert(key);
  root->use_count=this->use_count;
  root->elements= this->elements+1;
  root->maybe_flag=this->maybe_flag;
  return root;
}
