OnMessage(talk_base::Message *pmsg) {
  ASSERT(pmsg->message_id == kMessageAcceptConnection);
  talk_base::MessageData* data = pmsg->pdata;
  talk_base::AsyncSocket* socket =
      static_cast <talk_base::TypedMessageData<talk_base::AsyncSocket*>*>
      (data)->data();
  AcceptConnection(socket);
  delete data;
}
