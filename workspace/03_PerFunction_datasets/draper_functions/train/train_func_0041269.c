main(int argc, char *argv[])
{
   if (argc != 4)
     {
        printf("ARGS INCORRECT!\n");
        return 0;
     }
   sensor_type = atoi(argv[1]);
   sensor_name = strdup(argv[2]);
   if (!strcmp(sensor_name, "-null-"))
     E_FREE(sensor_name);
   poll_interval = atoi(argv[3]);
   cur_poll_interval = poll_interval;

   ecore_init();

   init();

   if (poller) ecore_poller_del(poller);
   poller = ecore_poller_add(ECORE_POLLER_CORE, cur_poll_interval,
                             poll_cb, NULL);
   poll_cb(NULL);

   ecore_main_loop_begin();
   ecore_shutdown();

   return 0;
}
