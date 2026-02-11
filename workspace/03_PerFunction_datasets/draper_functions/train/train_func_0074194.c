u_chnote(const userinput * const u) {
   int num = 0;
   xdcc *xd;

   updatecontext();

   if (u->arg1) num = atoi(u->arg1);

   if (num < 1 || num > irlist_size(&gdata.xdccs)) {
      u_respond(u,"Try Specifying a Valid Pack Number");
      return;
      }

   xd = irlist_get_nth(&gdata.xdccs, num-1);

   u_respond(u, "CHNOTE: [Pack %i] Old: %s New: %s",
             num,xd->note,
             u->arg2e ? u->arg2e : "");

   mydelete(xd->note);

   if (!u->arg2e)
     {
       xd->note = mymalloc(1);
       strcpy(xd->note,"");
     }
   else
     {
       xd->note = mymalloc(strlen(u->arg2e) + 1);
       strcpy(xd->note,u->arg2e);
     }

   write_statefile();
   xdccsavetext();

   }
