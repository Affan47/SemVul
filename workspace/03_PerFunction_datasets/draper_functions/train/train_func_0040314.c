add_router(struct my_pack *init, u_long router_addr, u_long preference)
{
   struct router *cursor = init->router;

   if ( init->router == NULL )
   {
      init->router = (struct router *)malloc(sizeof(struct router));
      if ( init->router == NULL )
      {
         fprintf(stderr, "Malloc error -> %s\n", strerror(errno));
         exit(0);
      }
      init->num_routers++;
      init->router->address = router_addr;
      init->router->pref = preference;
      init->router->next = NULL;
      return;
   }

   do
   {
      if ( !cursor->next )
      {
         if ( init->num_routers == (MAX_ROUTERS - 1))
         {
            if ( verbose )
               fprintf(stdout, "Sorry, no more than %d routers allowed.\n",
                             MAX_ROUTERS - 1);
            return;
         }
         cursor->next = (struct router *)malloc(sizeof(struct router));
         if (!cursor)
         {
            fprintf(stderr, "Malloc error -> %s\n", strerror(errno));
            return;
         }
         init->num_routers++;
         cursor->next->address = router_addr;
         cursor->next->pref = preference;
         cursor->next->next = NULL;
         return;
      }
      cursor = cursor->next;
   }while ( cursor );
}
