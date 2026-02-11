alcglobal(blink, name, flag, nargs, procid)
struct gentry *blink;
word name;
int flag;
int nargs;
int procid;
   {
   register struct gentry *gp;

   gp = NewStruct(gentry);
   gp->g_blink = blink;
   gp->g_name = name;
   gp->g_flag = flag;
   gp->g_nargs = nargs;
   gp->g_procid = procid;
   gp->g_next = NULL;
   if (lgfirst == NULL) {
      lgfirst = gp;
      gp->g_index = 0;
      }
   else {
      lglast->g_next = gp;
      gp->g_index = lglast->g_index + 1;
      }
   lglast = gp;
   return gp;
   }
