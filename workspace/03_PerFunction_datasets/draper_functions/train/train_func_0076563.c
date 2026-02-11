partial_send(struct ipmi_intf *intf, struct ipmi_rq *req, uint16_t *id)
{
  struct ipmi_rs *rsp;
  rsp = intf->sendrecv(intf, req);
  if (rsp == NULL) {
    return -1;
  }

  if (rsp->ccode || rsp->data_len < 2) {
    return -1;
  }

  *id = rsp->data[0] + (rsp->data[1] << 8);
  return 0;
}
