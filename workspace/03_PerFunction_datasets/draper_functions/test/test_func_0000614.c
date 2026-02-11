tcapsrt_call_matching(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree,
                      struct tcapsrt_info_t *p_tcapsrt_info)
{
  struct tcaphash_context_t *tcap_context=NULL;


  if(pinfo == NULL || pinfo->fd->num == 0) {
    return NULL;
  }

  switch (p_tcapsrt_info->ope) {

  case TC_BEGIN:
#ifdef DEBUG_TCAPSRT
    dbg(1,"\nTC_BEGIN ");
#endif
    tcap_context=tcaphash_begin_matching(tvb, pinfo, tree, p_tcapsrt_info);
    break;

  case TC_CONT:
#ifdef DEBUG_TCAPSRT
    dbg(1,"\nTC_CONT ");
#endif
    tcap_context=tcaphash_cont_matching(tvb, pinfo, tree, p_tcapsrt_info);
    break;

  case TC_ABORT:
#ifdef DEBUG_TCAPSRT
    dbg(1,"\nTC_ABORT ");
#endif
    tcap_context=tcaphash_end_matching(tvb, pinfo, tree, p_tcapsrt_info);
    break;

  case TC_END:
#ifdef DEBUG_TCAPSRT
    dbg(1,"\nTC_END ");
#endif
    tcap_context=tcaphash_end_matching(tvb, pinfo, tree, p_tcapsrt_info);
    break;

  case TC_ANSI_ALL:
  case TC_ANSI_ABORT:
#ifdef DEBUG_TCAPSRT
    dbg(1,"\nTC_ANSI ");
#endif
    tcap_context=tcaphash_ansi_matching(tvb, pinfo, tree, p_tcapsrt_info);
    break;

  default:
#ifdef DEBUG_TCAPSRT
    dbg(1,"\nUnknown %d ", p_tcapsrt_info->ope);
#endif
    break;
  }
#ifdef DEBUG_TCAPSRT
  if (tcap_context)
    dbg(1,"session %d ", tcap_context->session_id);
#endif
  return tcap_context;
}
