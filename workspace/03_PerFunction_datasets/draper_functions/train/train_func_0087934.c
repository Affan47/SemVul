handle_client_request(void *arg)
{
   FILE *events_file;
   char line[MAXSTRING];
   char errmsg[] = "Invalid command\n";
   char notavail[] = "Not available\n";
   char notrun[] = "Apcupsd not running\n";
   int nsockfd = ((struct s_arg *)arg)->newsockfd;
   UPSINFO *ups = ((struct s_arg *)arg)->ups;

   pthread_detach(pthread_self());
   if ((ups = attach_ups(ups)) == NULL) {
      net_send(nsockfd, notrun, sizeof(notrun));
      net_send(nsockfd, NULL, 0);
      free(arg);
      Error_abort0("Cannot attach SYSV IPC.\n");
   }

   for (;;) {

      if (net_recv(nsockfd, line, MAXSTRING) <= 0)
         break;

      if (strncmp("status", line, 6) == 0) {
         if (output_status(ups, nsockfd, status_open, status_write,
               status_close) < 0) {
            break;
         }
      } else if (strncmp("events", line, 6) == 0) {
         if ((ups->eventfile[0] == 0) ||
             ((events_file = fopen(ups->eventfile, "r")) == NULL)) {
            net_send(nsockfd, notavail, sizeof(notavail));
            if (net_send(nsockfd, NULL, 0) < 0)
               break;
         } else {
            int stat = output_events(nsockfd, events_file);

            fclose(events_file);
            if (stat < 0) {
               net_send(nsockfd, notavail, sizeof(notavail));
               net_send(nsockfd, NULL, 0);
               break;
            }
         }
      } else if (strncmp("rawupsinfo", line, 10) == 0) {
         net_send(nsockfd, (char *)ups, sizeof(UPSINFO));
         if (net_send(nsockfd, NULL, 0) < 0)
            break;
      } else if (strncmp("eprominfo", line, 9) == 0) {
         int len;

         len = strlen(ups->eprom) + 1;
         net_send(nsockfd, ups->eprom, len);
         len = strlen(ups->firmrev) + 1;
         net_send(nsockfd, ups->firmrev, len);
         len = strlen(ups->upsmodel) + 1;
         net_send(nsockfd, ups->upsmodel, len);

         if (net_send(nsockfd, NULL, 0) < 0)
            break;
      } else {
         net_send(nsockfd, errmsg, sizeof(errmsg));
         if (net_send(nsockfd, NULL, 0) < 0)
            break;
      }
   }

   net_close(nsockfd);

   free(arg);
   detach_ups(ups);
   return NULL;
}
