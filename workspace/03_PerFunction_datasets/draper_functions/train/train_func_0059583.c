u_mesq(const userinput * const u)
{
  int count;
  pqueue *pq;

  updatecontext();

  if (!u->arg1e || !strlen(u->arg1e))
    {
      u_respond(u,"Try Specifying a Message");
      return;
    }

  count=0;
  pq = irlist_get_head(&gdata.mainqueue);
  while(pq)
    {
      notice(pq->nick,"MESSAGE FROM OWNER: %s",u->arg1e);
      count++;
      pq = irlist_get_next(pq);
    }

  u_respond(u,"Sent message to %i user%s",count,count!=1?"s":"");

}
