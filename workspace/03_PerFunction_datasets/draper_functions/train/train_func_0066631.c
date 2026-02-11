evtag_unmarshal_msg(struct evbuffer *evbuf, ev_uint32_t need_tag, struct msg *msg)
{
  ev_uint32_t tag;
  int res = -1;

  struct evbuffer *tmp = evbuffer_new();

  if (evtag_unmarshal(evbuf, &tag, tmp) == -1 || tag != need_tag)
    goto error;

  if (msg_unmarshal(msg, tmp) == -1)
    goto error;

  res = 0;

 error:
  evbuffer_free(tmp);
  return (res);
}
