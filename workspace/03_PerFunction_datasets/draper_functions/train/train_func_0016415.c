u_nomax(const userinput * const u)
{
  int num = -1;
  transfer *tr;

  updatecontext();

  if (u->arg1) num = atoi(u->arg1);

  if ((num < 0) || !does_tr_id_exist(num))
    {
      u_respond(u,"Invalid ID number, Try \"DCL\" for a list");
    }
  else
    {
      tr = does_tr_id_exist(num);
      tr->nomax = 1;
    }
}
