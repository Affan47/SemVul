dissect_t124_heur(tvbuff_t *tvb, packet_info *pinfo, proto_tree *parent_tree, void *data _U_)
{
  asn1_ctx_t asn1_ctx;
  volatile gboolean failed = FALSE;

  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);

  t124Identifier = NULL;


  TRY {
    (void) dissect_per_sequence(tvb, 0, &asn1_ctx, NULL, hf_t124_connectGCCPDU, -1, t124Heur_sequence);
  } CATCH_BOUNDS_ERRORS {
    failed = TRUE;
  } ENDTRY;

  if (!failed && ((t124Identifier != NULL) &&
                  (strcmp(t124Identifier, "0.0.20.124.0.1") == 0))) {
    dissect_t124(tvb, pinfo, parent_tree);

    return TRUE;
  }

  return FALSE;
}
