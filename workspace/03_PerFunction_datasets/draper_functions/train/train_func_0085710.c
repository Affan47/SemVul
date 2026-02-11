json_artifact_ticket( cson_object * zParent, int rid ){
  cson_object * pay = NULL;
  Manifest *pTktChng = NULL;
  static cson_value * eventTypeLabel = NULL;
  if(! g.perm.RdTkt ){
    g.json.resultCode = FSL_JSON_E_DENIED;
    return NULL;
  }
  if(!eventTypeLabel){
    eventTypeLabel = json_new_string("ticket");
    json_gc_add("$EVENT_TYPE_LABEL(ticket)", eventTypeLabel);
  }

  pTktChng = manifest_get(rid, CFTYPE_TICKET);
  if( pTktChng==0 ){
    g.json.resultCode = FSL_JSON_E_MANIFEST_READ_FAILED;
    return NULL;
  }
  pay = cson_new_object();
  cson_object_set(pay, "eventType", eventTypeLabel );
  cson_object_set(pay, "uuid", json_new_string(pTktChng->zTicketUuid));
  cson_object_set(pay, "user", json_new_string(pTktChng->zUser));
  cson_object_set(pay, "timestamp", json_julian_to_timestamp(pTktChng->rDate));
  manifest_destroy(pTktChng);
  return cson_object_value(pay);
}
