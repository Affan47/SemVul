u_qsend(const userinput * const u)
{

  updatecontext();

  if (!irlist_size(&gdata.mainqueue))
    {
      u_respond(u,"No Users Queued");
      return;
    }

  if (irlist_size(&gdata.trans) >= MAXTRANS)
    {
      u_respond(u,"Too many transfers");
      return;
    }

  sendaqueue(2);
  return;
}
