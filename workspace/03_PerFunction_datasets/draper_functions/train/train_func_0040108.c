soap_wsrm_disconnect(struct soap *soap)
{ struct soap_wsrm_data *data = (struct soap_wsrm_data*)soap_lookup_plugin(soap, soap_wsrm_id);
  DBGFUN("soap_wsrm_disconnect");
  if (data->fdisconnect && data->fdisconnect(soap))
    return soap->error;
  if (data->seq)
  { soap_wsrm_seq_release(soap, data->seq);
    data->seq = NULL;
  }
  if (data->msg)
  { if (data->msg->list)
    { data->state = SOAP_WSRM_OFF;
      data->msg = NULL;
    }
  }
  return SOAP_OK;
}
