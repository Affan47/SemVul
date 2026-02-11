do_mount_cmd(UAContext *ua, const char *command)
{
   USTORE store;
   BSOCK *sd;
   JCR *jcr = ua->jcr;
   char dev_name[MAX_NAME_LENGTH];
   int drive;
   int slot = -1;

   if (!open_client_db(ua)) {
      return;
   }
   Dmsg2(120, "%s: %s\n", command, ua->UA_sock->msg);

   store.store = get_storage_resource(ua, true);
   if (!store.store) {
      return;
   }
   pm_strcpy(store.store_source, _("unknown source"));
   set_wstorage(jcr, &store);
   drive = get_storage_drive(ua, store.store);
   if (strcmp(command, "mount") == 0) {
      slot = get_storage_slot(ua, store.store);
   }

   Dmsg3(120, "Found storage, MediaType=%s DevName=%s drive=%d\n",
      store.store->media_type, store.store->dev_name(), drive);

   if (!connect_to_storage_daemon(jcr, 10, SDConnectTimeout, 1)) {
      ua->error_msg(_("Failed to connect to Storage daemon.\n"));
      return;
   }
   sd = jcr->store_bsock;
   bstrncpy(dev_name, store.store->dev_name(), sizeof(dev_name));
   bash_spaces(dev_name);
   if (slot > 0) {
      sd->fsend("%s %s drive=%d slot=%d", command, dev_name, drive, slot);
   } else {
      sd->fsend("%s %s drive=%d", command, dev_name, drive);
   }
   while (sd->recv() >= 0) {
      ua->send_msg("%s", sd->msg);
   }
   sd->signal(BNET_TERMINATE);
   sd->close();
   jcr->store_bsock = NULL;
}
