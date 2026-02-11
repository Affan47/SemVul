addtoqueue(const char* nick, const char* hostname, int pack)
{
   char *tempstr = mycalloc(maxtextlength);
   pqueue *tempq;
   xdcc *tempx;
   int inq,alreadytrans;
   pqueue *pq;

   updatecontext();

   tempx = irlist_get_nth(&gdata.xdccs, pack-1);

   alreadytrans = inq = 0;
   pq = irlist_get_head(&gdata.mainqueue);
   while(pq)
     {
       if (!strcmp(pq->hostname,hostname))
         {
           inq++;
           if (pq->xpack == tempx)
             {
               alreadytrans++;
             }
         }
       pq = irlist_get_next(pq);
     }

   if (alreadytrans) {
      ioutput(CALLTYPE_MULTI_MIDDLE,OUT_S|OUT_L|OUT_D,COLOR_YELLOW," Denied (queue/dup): ");
      snprintf(tempstr, maxtextlength,
               "Denied, You already have that item queued.");
      return tempstr;
      }

   if (inq >= gdata.maxqueueditemsperperson) {
      ioutput(CALLTYPE_MULTI_MIDDLE,OUT_S|OUT_L|OUT_D,COLOR_YELLOW," Denied (user/queue): ");
      snprintf(tempstr, maxtextlength,
               "Denied, You already have %i items queued, Try Again Later",
               inq);
      return tempstr;
      }

      if (irlist_size(&gdata.mainqueue) >= gdata.queuesize) {
         ioutput(CALLTYPE_MULTI_MIDDLE,OUT_S|OUT_L|OUT_D,COLOR_YELLOW," Denied (slot/queue): ");
         snprintf(tempstr, maxtextlength,
                  "Main queue of size %d is Full, Try Again Later",
                  gdata.queuesize);
         }
      else {
         ioutput(CALLTYPE_MULTI_MIDDLE,OUT_S|OUT_L|OUT_D,COLOR_YELLOW," Queued (slot): ");
         tempq = irlist_add(&gdata.mainqueue, sizeof(pqueue));
         tempq->queuedtime = gdata.curtime;
         tempq->nick = mymalloc(strlen(nick)+1);
         strcpy(tempq->nick,nick);
         tempq->hostname = mymalloc(strlen(hostname)+1);
         strcpy(tempq->hostname,hostname);
         tempq->xpack = tempx;

         snprintf(tempstr,maxtextlength,
                  "Added you to the main queue in position %d. To Remove youself at "
                  "a later time type \"/msg %s xdcc remove\".",
                  irlist_size(&gdata.mainqueue),
                  (gdata.user_nick ? gdata.user_nick : "??"));
         }
   return tempstr;
   }
