Curl_move_handle_from_send_to_recv_pipe(struct SessionHandle *handle,
                                             struct connectdata *conn)
{
  struct curl_llist_element *curr;

  curr = conn->send_pipe->head;
  while(curr) {
    if(curr->ptr == handle) {
      Curl_llist_move(conn->send_pipe, curr,
                      conn->recv_pipe, conn->recv_pipe->tail);

      if(conn->send_pipe->head) {


        conn->writechannel_inuse = FALSE;
#ifdef DEBUGBUILD
        infof(conn->data, "%p is at send pipe head B!\n",
              (void *)conn->send_pipe->head->ptr);
#endif
        Curl_expire(conn->send_pipe->head->ptr, 1);
      }


      break;
    }
    curr = curr->next;
  }
}
