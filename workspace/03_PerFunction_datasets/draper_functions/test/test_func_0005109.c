process(void *a) {
  process_arg_t *arg = (process_arg_t *)a;
  if(arg->query.empty())
    Error(arg->file, 53, "Empty query");
  else if(*arg->query.begin() == "BIND")
    arg->server->Bind(arg->file);
  else if(*arg->query.begin() == "ADD")
    arg->server->Add(arg->file, arg->query);
  else if(*arg->query.begin() == "SEARCH")
    arg->server->Search(arg->file, arg->query);
  else
    Error(arg->file, 53, "Unimplemented query type: " + *arg->query.begin());
  delete arg;
  return NULL;
}
