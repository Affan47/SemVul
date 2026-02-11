dump(void)
{
  CMD_Repository::iterator it;

  DBG(0, form("KCemu/CMD_Repository",
              "*** CMD_Repository dump ***************************\n"));
  for (it = _cmd_llist->begin(); it != _cmd_llist->end();it++)
    {
      DBG(0, form("KCemu/CMD_Repository",
                  "+ List: %s\n", (*it)->get_name()));
      (*it)->dump();
    }
  DBG(0, form("KCemu/CMD_Repository",
              "*** CMD_Repository ********************************\n"));
}
