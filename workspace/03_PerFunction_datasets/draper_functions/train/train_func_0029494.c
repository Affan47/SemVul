isexpired (pw, sp)
       const struct passwd *pw;
       const struct spwd *sp;
{
       long    now;
       now = time ((time_t *) 0) / SCALE;


       if (sp->sp_expire > 0 && sp->sp_expire < now)
               return 3;


       if (sp->sp_lstchg == 0)
               return 1;

       if (sp->sp_inact > 0 && sp->sp_lstchg > 0 && sp->sp_max > 0 &&
                       sp->sp_inact + sp->sp_lstchg + sp->sp_max < now)
               return 2;


       if (sp->sp_lstchg == -1 ||
                       sp->sp_max == -1 || sp->sp_max >= (10000L*DAY/SCALE))
               return 0;


       if (sp->sp_lstchg + sp->sp_max < now)
               return 1;
       return 0;
}
