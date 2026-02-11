status_content(UAContext *ua, STORE *store)
{
   int Slot, Drive;
   char type;
   char dev_name[MAX_NAME_LENGTH];
   char vol_name[MAX_NAME_LENGTH];
   BSOCK *sd;
   vol_list_t *vl=NULL, *vol_list = NULL;

   if (!(sd=open_sd_bsock(ua))) {
      return;
   }

   if (!open_client_db(ua)) {
      return;
   }

   bstrncpy(dev_name, store->dev_name(), sizeof(dev_name));
   bash_spaces(dev_name);

   bnet_fsend(sd, NT_("autochanger listall %s \n"), dev_name);


   while (bnet_recv(sd) >= 0) {
      strip_trailing_junk(sd->msg);


      if (sd->msg[0] == '3'     && B_ISDIGIT(sd->msg[1]) &&
          B_ISDIGIT(sd->msg[2]) && B_ISDIGIT(sd->msg[3]) &&
          sd->msg[4] == ' ') {
         ua->send_msg("%s\n", sd->msg);
         continue;
      }

      Drive = Slot = -1;
      *vol_name = 0;

      if (sscanf(sd->msg, "D:%d:F:%d:%127s", &Drive, &Slot, vol_name) == 3) {
         ua->send_msg("D|%d|%d|%s\n", Drive, Slot, vol_name);


         if (*vol_name) {

            vl = (vol_list_t *)malloc(sizeof(vol_list_t));
            vl->Slot = Slot;
            vl->VolName = bstrdup(vol_name);
            vl->next = vol_list;
            vol_list = vl;
         }

      } else if (sscanf(sd->msg, "D:%d:E", &Drive) == 1) {
         ua->send_msg("D|%d||\n", Drive);

      } else if (sscanf(sd->msg, "%c:%d:F:%127s", &type, &Slot, vol_name)== 3) {
         content_send_info(ua, type, Slot, vol_name);

      } else if (sscanf(sd->msg, "%c:%d:E", &type, &Slot) == 2) {

         vol_list_t *prev=NULL;
         for (vl = vol_list; vl; vl = vl->next) {
            if (vl->Slot == Slot) {
               bstrncpy(vol_name, vl->VolName, MAX_NAME_LENGTH);


               if (prev) {
                  prev->next = vl->next;
               } else {
                  vol_list = vl->next;
               }
               free(vl->VolName);
               free(vl);
               break;
            }
            prev = vl;
         }
         content_send_info(ua, type, Slot, vol_name);

      } else {
         Dmsg1(10, "Discarding msg=%s\n", sd->msg);
      }
   }
   close_sd_bsock(ua);
}
