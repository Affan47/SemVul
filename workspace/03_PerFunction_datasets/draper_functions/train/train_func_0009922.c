_new_local_candidate (FsStream *stream, FsCandidate *candidate)
{
  Tcl_Obj *tcl_candidate = NULL;
  Tcl_Obj *elements[11];
  Tcl_Obj **local_candidates = NULL;

  if (stream == audio_stream)
    local_candidates = &audio_local_candidates;
  else
    local_candidates = &video_local_candidates;

  if (*local_candidates == NULL) {
    *local_candidates = Tcl_NewListObj (0, NULL);
    Tcl_IncrRefCount(*local_candidates);
  }

  elements[0] = Tcl_NewStringObj (candidate->foundation == NULL ?
      "" : candidate->foundation, -1);
  elements[1] = Tcl_NewIntObj (candidate->component_id);
  elements[2] = Tcl_NewStringObj (candidate->ip, -1);
  elements[3] = Tcl_NewIntObj (candidate->port);
  elements[4] = Tcl_NewStringObj (candidate->base_ip, -1);
  elements[5] = Tcl_NewIntObj (candidate->base_port);
  elements[6] = Tcl_NewStringObj (candidate->proto == FS_NETWORK_PROTOCOL_UDP ?
      "UDP" : "TCP", -1);
  if (call_type & RTP_ICE6)
    elements[7] = Tcl_NewDoubleObj ((gfloat) candidate->priority / 1000);
  else
    elements[7] = Tcl_NewIntObj (candidate->priority);

  elements[8] = Tcl_NewStringObj (
      _fs_candidate_type_to_string (candidate->type), -1);

  elements[9] = Tcl_NewStringObj (candidate->username == NULL ?
      "" : candidate->username, -1);
  elements[10] = Tcl_NewStringObj (candidate->password == NULL ?
      "" : candidate->password, -1);
  tcl_candidate = Tcl_NewListObj (11, elements);

  Tcl_ListObjAppendElement(NULL, *local_candidates, tcl_candidate);

}
