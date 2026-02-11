vtty_create(vm_instance_t *vm,char *name,int type,int tcp_port,
                    const vtty_serial_option_t *option)
{
   vtty_t *vtty;
   int i;

   if (!(vtty = malloc(sizeof(*vtty)))) {
      fprintf(stderr,"VTTY: unable to create new virtual tty.\n");
      return NULL;
   }
   memset(vtty,0,sizeof(*vtty));
   vtty->name = name;
   vtty->type = type;
   vtty->vm   = vm;
   vtty->fd_count = 0;
   pthread_mutex_init(&vtty->lock,NULL);
   vtty->terminal_support = 1;
   vtty->input_state = VTTY_INPUT_TEXT;
   fd_pool_init(&vtty->fd_pool);
   for(i=0;i<VTTY_MAX_FD;i++)
       vtty->fd_array[i] = -1;

   switch (vtty->type) {
      case VTTY_TYPE_NONE:
         break;

      case VTTY_TYPE_TERM:
         vtty_term_init();
         vtty->fd_array[0] = STDIN_FILENO;
         break;

      case VTTY_TYPE_TCP:
         vtty->tcp_port = tcp_port;
         vtty->fd_count = vtty_tcp_conn_wait(vtty);
         break;

      case VTTY_TYPE_SERIAL:
         vtty->fd_array[0] = open(option->device, O_RDWR);
         if (vtty->fd_array[0] < 0) {
            fprintf(stderr,"VTTY: open failed\n");
            free(vtty);
            return NULL;
         }
         if (vtty_serial_setup(vtty,option)) {
            fprintf(stderr,"VTTY: setup failed\n");
            close(vtty->fd_array[0]);
            free(vtty);
            return NULL;
         }
         vtty->terminal_support = 0;
         break;

      default:
         fprintf(stderr,"tty_create: bad vtty type %d\n",vtty->type);
         return NULL;
   }


   VTTY_LIST_LOCK();
   vtty->next = vtty_list;
   vtty->pprev = &vtty_list;

   if (vtty_list != NULL)
      vtty_list->pprev = &vtty->next;

   vtty_list = vtty;
   VTTY_LIST_UNLOCK();
   return vtty;
}
