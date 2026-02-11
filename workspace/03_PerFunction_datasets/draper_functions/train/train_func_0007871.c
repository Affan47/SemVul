soap_smd_end(struct soap *soap, char *buf, int *len)
{ struct soap_smd_data *data;
  int err;
  data = (struct soap_smd_data*)soap->data[0];
  if (!data)
  { if (soap->error)
      return soap->error;
    return soap->error = SOAP_USER_ERROR;
  }


  err = soap_smd_final(soap, data, buf, len);

  soap->fsend = data->fsend;
  soap->frecv = data->frecv;

  soap->mode = data->mode;

  SOAP_FREE(soap, data);
  soap->data[0] = NULL;

  return err;
}
