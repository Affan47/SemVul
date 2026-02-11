get_client_class(struct Client *acptr)
{
  struct SLink *tmp;
  struct ConnectionClass *cl;


  if (acptr && !IsMe(acptr) && (cli_confs(acptr)))
    for (tmp = cli_confs(acptr); tmp; tmp = tmp->next)
    {
      if (tmp->value.aconf && (cl = tmp->value.aconf->conn_class))
        return ConClass(cl);
    }
  return "(null-class)";
}
