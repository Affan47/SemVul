_e_mod_notify_merge(E_Notification *n)
{
   Ind_Notify_Win *nwin;
   const Eina_List *l;
   const char *appname, *bold, *bnew;

   if (!n) return NULL;
   if (!(appname = e_notification_app_name_get(n))) return NULL;
   EINA_LIST_FOREACH(_nwins, l, nwin)
     {
        const char *name;

        if (!nwin->notify) continue;
        if (!(name = e_notification_app_name_get(nwin->notify))) continue;
        if (!strcmp(appname, name)) break;
     }
   if (!nwin) return NULL;

   bold = e_notification_body_get(nwin->notify);
   bnew = e_notification_body_get(n);


   if (!strcmp(bold, bnew)) return nwin;

   e_notification_body_set(n, bnew);

   e_notification_unref(nwin->notify);
   nwin->notify = n;
   e_notification_ref(nwin->notify);

   return nwin;
}
