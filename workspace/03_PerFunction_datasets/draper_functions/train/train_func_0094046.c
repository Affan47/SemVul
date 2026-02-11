u_closeu(const userinput * const u)
{
  int num = -1;
  upload *ul;

  updatecontext();

  if (u->arg1) num = atoi(u->arg1);

  if ((num < 0) || (num >= irlist_size(&gdata.uploads)))
    {
      u_respond(u,"Invalid ID number, Try \"DCL\" for a list");
    }
  else
    {
      ul = irlist_get_nth(&gdata.uploads, num);

      l_closeconn(ul,"Owner Requested Close",0);
    }
}
