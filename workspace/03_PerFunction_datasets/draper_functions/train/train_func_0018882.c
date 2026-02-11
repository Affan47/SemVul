buffer_body(struct soap *sender)
{ char *s;
  if (!soap_new_block(sender))
    return sender->error;
  for (;;)
  { if (!(s = (char*)soap_push_block(sender, NULL, sender->buflen - sender->bufidx)))
      return SOAP_EOM;
    memcpy(s, sender->buf + sender->bufidx, sender->buflen - sender->bufidx);
    if (soap_recv_raw(sender))
      break;
  }
  if (sender->error == SOAP_EOF)
    sender->error = SOAP_OK;
  if (sender->error || soap_end_recv(sender))
    return sender->error;
  sender->length = sender->blist->size;
  return SOAP_OK;
}
