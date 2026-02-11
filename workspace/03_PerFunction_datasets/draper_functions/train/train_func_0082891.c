e_hints_client_stacking_set(void)
{
   Eina_List *ml = NULL, *cl = NULL;
   unsigned int i = 0, num = 0;
   E_Manager *m;
   E_Container *c;
   E_Border_List *bl;
   E_Border *b;
   Ecore_X_Window *clients = NULL;


   EINA_LIST_FOREACH(e_manager_list(), ml, m)
     {
        EINA_LIST_FOREACH(m->containers, cl, c)
          {
             num += e_container_borders_count(c);
          }
     }

   if (num > 0)
     {
        clients = calloc(num, sizeof(Ecore_X_Window));
        if (!clients) return;

        EINA_LIST_FOREACH(e_manager_list(), ml, m)
          {
             EINA_LIST_FOREACH(m->containers, cl, c)
               {
                  bl = e_container_border_list_first(c);
                  while ((b = e_container_border_list_next(bl)))
                    {
                       if (i >= num)
                         {
                            e_error_message_show("e_hints.c: e_hints_client_stacking_set()\n"
                                                 "\n"
                                                 "Window list size greater than window count.\n"
                                                 "This is really bad.\n"
                                                 "Please report this.\n");
                            break;
                         }
                       clients[i++] = b->client.win;
                    }
                  e_container_border_list_free(bl);
               }
          }
        if (i < num)
          {
             e_error_message_show("e_hints.c: e_hints_client_stacking_set()\n"
                                  "\n"
                                  "Window list size less than window count.\n"
                                  "This is strange, but not harmful.\n"
                                  "Please report this.\n");
          }
        EINA_LIST_FOREACH(e_manager_list(), ml, m)
          {
             ecore_x_netwm_client_list_stacking_set(m->root, clients, num);
          }
        E_FREE(clients);
     }
   else
     {
        EINA_LIST_FOREACH(e_manager_list(), ml, m)
          {
             ecore_x_netwm_client_list_stacking_set(m->root, NULL, 0);
          }
     }
}
