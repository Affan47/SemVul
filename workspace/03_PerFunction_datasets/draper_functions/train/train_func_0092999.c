unbind(gemreceive*x, t_symbol*key) {
  t_gemreceive_proxy*list=0, *last=0;
  t_bind_element*elements=0, *lastlmn=0;

  debug_post("trying to unbind 0x%X:: '%s' from %x", x, key->s_name, proxy_list);

  for(list=proxy_list; list && list->key!=key; list=list->next){
    last=list;
  }
  if(!list)return;

  for(elements=list->elements; elements && elements->object != x; elements=elements->next) {
    lastlmn=elements;
  }

  if(elements) {

    if(lastlmn) {
      lastlmn->next=elements->next;
    } else {
      list->elements=elements->next;
    }

    elements->object=0;
    elements->priority=0;
    elements->next=0;

    freebytes(elements, sizeof(elements));
  } else {

  }

  if(0==list->elements) {

    if(last) {
      last->next=list->next;
    } else {
      proxy_list=list->next;
    }

    pd_unbind(&list->p_obj.ob_pd, list->key);
    list->next=0;
    list->key=0;

    pd_free(&list->p_obj.ob_pd);
  }
}
