_ipmi_ssif_cmd_write (ipmi_ssif_ctx_t ctx,
                      uint8_t lun,
                      uint8_t net_fn,
                      fiid_obj_t obj_cmd_rq)
{
  uint8_t *pkt = NULL;
  unsigned int pkt_len;
  int hdr_len, cmd_len, rv = -1;
  fiid_obj_t obj_hdr = NULL;

  assert (ctx);
  assert (ctx->magic == IPMI_SSIF_CTX_MAGIC);
  assert (IPMI_BMC_LUN_VALID (lun));
  assert (IPMI_NET_FN_RQ_VALID (net_fn));
  assert (fiid_obj_valid (obj_cmd_rq));
  assert (fiid_obj_packet_valid (obj_cmd_rq) == 1);

  if ((hdr_len = fiid_template_len_bytes (tmpl_hdr_kcs)) < 0)
    {
      SSIF_ERRNO_TO_SSIF_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if ((cmd_len = fiid_obj_len_bytes (obj_cmd_rq)) < 0)
    {
      SSIF_FIID_OBJECT_ERROR_TO_SSIF_ERRNUM (ctx, obj_cmd_rq);
      goto cleanup;
    }

  if (!(obj_hdr = fiid_obj_create (tmpl_hdr_kcs)))
    {
      SSIF_ERRNO_TO_SSIF_ERRNUM (ctx, errno);
      goto cleanup;
    }

  pkt_len = hdr_len + cmd_len;

  if (!(pkt = (uint8_t *)malloc (pkt_len)))
    {
      SSIF_SET_ERRNUM (ctx, IPMI_SSIF_ERR_OUT_OF_MEMORY);
      goto cleanup;
    }

  memset (pkt, 0, pkt_len);

  if (fill_hdr_ipmi_kcs (lun,
                         net_fn,
                         obj_hdr) < 0)
    {
      SSIF_SET_ERRNUM (ctx, IPMI_SSIF_ERR_INTERNAL_ERROR);
      goto cleanup;
    }

  if (assemble_ipmi_kcs_pkt (obj_hdr,
                             obj_cmd_rq,
                             pkt,
                             pkt_len,
			     IPMI_INTERFACE_FLAGS_DEFAULT) < 0)
    {
      SSIF_SET_ERRNUM (ctx, IPMI_SSIF_ERR_INTERNAL_ERROR);
      goto cleanup;
    }

  if (ipmi_ssif_write (ctx, pkt, pkt_len) < 0)
    goto cleanup;

  rv = 0;
 cleanup:
  fiid_obj_destroy (obj_hdr);
  free (pkt);
  return (rv);
}
