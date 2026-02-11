soap_smd_recv(struct soap *soap, char *buf, size_t len)
{ size_t ret = ((struct soap_smd_data*)soap->data[0])->frecv(soap, buf, len);
  if (ret && soap_smd_update(soap, (struct soap_smd_data*)soap->data[0], buf, ret))
    return 0;
  return ret;
}
