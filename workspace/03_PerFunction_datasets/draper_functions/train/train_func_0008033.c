free_client(struct Client *client_p)
{
  assert(client_p != NULL);
  assert(client_p != &me);
  assert(client_p->hnext == client_p);
  assert(client_p->channel.head == NULL);
  assert(dlink_list_length(&client_p->channel) == 0);

  MyFree(client_p->away);
  MyFree(client_p->serv);

  if (MyConnect(client_p))
  {
    assert(client_p->localClient->invited.head == NULL);
    assert(dlink_list_length(&client_p->localClient->invited) == 0);
    assert(IsClosing(client_p) && IsDead(client_p));

    MyFree(client_p->localClient->response);
    MyFree(client_p->localClient->auth_oper);


    if (client_p->localClient->listener)
    {
      assert(0 < client_p->localClient->listener->ref_count);
      if (0 == --client_p->localClient->listener->ref_count &&
          !client_p->localClient->listener->active)
        free_listener(client_p->localClient->listener);
    }

    dbuf_clear(&client_p->localClient->buf_recvq);
    dbuf_clear(&client_p->localClient->buf_sendq);

    BlockHeapFree(lclient_heap, client_p->localClient);
  }

  BlockHeapFree(client_heap, client_p);
}
