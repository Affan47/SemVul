fdh_func(Pulse *conn, Ecore_Fd_Handler *fdh)
{
   Pulse_Tag *rprev, *wprev;
   int pa_read, pa_write;

   if (conn->watching) pa_read = ECORE_FD_READ;
   else
     pa_read = !!ecore_main_fd_handler_active_get(fdh, ECORE_FD_READ) * ECORE_FD_READ;
   pa_write = !!ecore_main_fd_handler_active_get(fdh, ECORE_FD_WRITE) * ECORE_FD_WRITE;
   rprev = eina_list_data_get(conn->iq);
   wprev = eina_list_data_get(conn->oq);

   switch (conn->state)
     {
      case PA_STATE_INIT:
        if (!wprev)
          {
             wprev = login_setup(conn);
             conn->oq = eina_list_append(conn->oq, wprev);
          }

        if (!wprev->auth)
          msg_sendmsg_creds(conn, wprev);


        if (wprev->auth && msg_send(conn, wprev))
          {
             conn->state++;
             ecore_main_fd_handler_active_set(fdh, ECORE_FD_READ);
          }
        break;
      case PA_STATE_AUTH:
        if (pulse_recv(conn, fdh, NULL))
          login_finish(conn, fdh);
        break;
      case PA_STATE_MOREAUTH:
        if (pa_write)
          {
             if (msg_send(conn, wprev))
               ecore_main_fd_handler_active_set(fdh, ECORE_FD_READ);
             break;
          }
        if (pulse_recv(conn, fdh, NULL))
          {
             conn->state++;
             INF("Login complete!");
             ecore_main_fd_handler_active_set(fdh, 0);
             ecore_event_add(PULSE_EVENT_CONNECTED, conn, pulse_fake_free, NULL);
          }
        break;
      case PA_STATE_CONNECTED:
        if (pa_write)
          {
             if (wprev)
               {
                  DBG("write");
                  if (!wprev->auth)
                    msg_send_creds(conn, wprev);
                  if (wprev->auth)
                    {
                       if (msg_send(conn, wprev))
                         ecore_main_fd_handler_active_set(conn->fdh, ECORE_FD_READ | (!!conn->oq * ECORE_FD_WRITE));
                    }
               }
             else
               ecore_main_fd_handler_active_set(conn->fdh, ECORE_FD_READ);
          }
        if (pa_read)
          {
             DBG("read");
             if ((!rprev) || (!rprev->auth) || (rprev->pos < rprev->dsize))
               {
                  Pulse_Tag *tag;
                  PA_Commands command;
                  if (!pulse_recv(conn, fdh, &tag)) break;

                  command = (uintptr_t)eina_hash_find(conn->tag_handlers, &tag->tag_count);
                  eina_hash_del_by_key(conn->tag_handlers, &tag->tag_count);
                  deserialize_tag(conn, command, tag);
                  if (!eina_list_count(conn->oq))
                    ecore_main_fd_handler_active_set(conn->fdh, pa_write | conn->watching * ECORE_FD_READ);
                  pulse_tag_free(tag);
               }
          }
      default:
        break;
     }

   return ECORE_CALLBACK_RENEW;
}
