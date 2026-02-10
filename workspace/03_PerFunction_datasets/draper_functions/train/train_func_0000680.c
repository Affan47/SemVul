clone_req_option_list (ReqOption *req_option)
{
  ReqOption *new_req_option;

  if (req_option == NULL)
    return NULL;

  new_req_option = (ReqOption *) xmalloc (sizeof (ReqOption));
  new_req_option->or_option_terms = NULL;
  new_req_option->next = NULL;
  new_req_option->or_option_terms =
    clone_req_or_option_list (req_option->or_option_terms);
  new_req_option->next = clone_req_option_list (req_option->next);
  return new_req_option;
}
