__wsrm__CloseSequence(struct soap *soap, struct wsrm__CloseSequenceType *req, struct wsrm__CloseSequenceResponseType *res)
{ struct soap_wsrm_sequence *seq;
  struct soap_wsrm_data *data;
  char *action;
  DBGFUN("__wsrm__CloseSequence");
  if (soap_wsa_check(soap))
    return soap->error;
  data = (struct soap_wsrm_data*)soap_lookup_plugin(soap, soap_wsrm_id);
  if (!data)
    return soap->error = SOAP_PLUGIN_ERROR;
  data->state = SOAP_WSRM_OFF;
  if (!req)
    return soap_wsrm_error(soap, NULL, wsrm__WSRMRequired);
  MUTEX_LOCK(soap_wsrm_session_lock);
  seq = soap_wsrm_seq_lookup_ack(data, req->Identifier);
  if (!seq)
  { MUTEX_UNLOCK(soap_wsrm_session_lock);
    return soap_wsrm_error(soap, NULL, wsrm__UnknownSequence);
  }
  if (seq->state == SOAP_WSRM_TERMINATED)
  { soap_wsrm_error(soap, seq, wsrm__SequenceTerminated);
    MUTEX_UNLOCK(soap_wsrm_session_lock);
    return soap->error;
  }
  if (req->LastMsgNumber)
    seq->lastnum = *req->LastMsgNumber;
  seq->state = SOAP_WSRM_CLOSED;
  res->Identifier = req->Identifier;
  soap->header->wsrm__Sequence = NULL;
  if (!soap->header->wsrm__SequenceAcknowledgement && !(soap->header->wsrm__SequenceAcknowledgement = (struct _wsrm__SequenceAcknowledgement*)soap_malloc(soap, sizeof(struct _wsrm__SequenceAcknowledgement))))
  { MUTEX_UNLOCK(soap_wsrm_session_lock);
    return soap->error;
  }
  soap->header->__sizeSequenceAcknowledgement = 1;
  if (soap_wsrm_set_ack(soap, seq, soap->header->wsrm__SequenceAcknowledgement))
  { MUTEX_UNLOCK(soap_wsrm_session_lock);
    return soap->error;
  }
  soap_wsa_add_ReplyTo(soap, seq->to);
  MUTEX_UNLOCK(soap_wsrm_session_lock);
  action = (char*)soap_malloc(soap, strlen(soap->action) + 9);
  strcpy(action, soap->action);
  strcat(action, "Response");
  return soap_wsa_reply(soap, NULL, action);
}
