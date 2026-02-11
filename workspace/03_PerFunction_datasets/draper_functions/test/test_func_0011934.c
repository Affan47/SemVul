ipmi_sdr_parse_record_id_and_type (ipmi_sdr_parse_ctx_t ctx,
                                   const void *sdr_record,
                                   unsigned int sdr_record_len,
                                   uint16_t *record_id,
                                   uint8_t *record_type)
{
  fiid_obj_t obj_sdr_record_header = NULL;
  int sdr_record_header_len;
  uint64_t val;
  int rv = -1;

  if (!ctx || ctx->magic != IPMI_SDR_PARSE_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_sdr_parse_ctx_errormsg (ctx), ipmi_sdr_parse_ctx_errnum (ctx));
      return (-1);
    }

  if (!sdr_record || !sdr_record_len)
    {
      SDR_PARSE_SET_ERRNUM (ctx, IPMI_SDR_PARSE_ERR_PARAMETERS);
      return (-1);
    }

  if ((sdr_record_header_len = fiid_template_len_bytes (tmpl_sdr_record_header)) < 0)
    {
      SDR_PARSE_ERRNO_TO_SDR_PARSE_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (sdr_record_len < sdr_record_header_len)
    {
      SDR_PARSE_SET_ERRNUM (ctx, IPMI_SDR_PARSE_ERR_INCOMPLETE_SDR_RECORD);
      goto cleanup;
    }

  if (!(obj_sdr_record_header = fiid_obj_create (tmpl_sdr_record_header)))
    {
      SDR_PARSE_ERRNO_TO_SDR_PARSE_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (fiid_obj_set_all (obj_sdr_record_header,
                        sdr_record,
                        sdr_record_header_len) < 0)
    {
      SDR_PARSE_FIID_OBJECT_ERROR_TO_SDR_PARSE_ERRNUM (ctx, obj_sdr_record_header);
      goto cleanup;
    }

  if (record_id)
    {
      if (FIID_OBJ_GET (obj_sdr_record_header,
                        "record_id",
                        &val) < 0)
        {
          SDR_PARSE_FIID_OBJECT_ERROR_TO_SDR_PARSE_ERRNUM (ctx, obj_sdr_record_header);
          goto cleanup;
        }
      *record_id = val;
    }

  if (record_type)
    {
      if (FIID_OBJ_GET (obj_sdr_record_header,
                        "record_type",
                        &val) < 0)
        {
          SDR_PARSE_FIID_OBJECT_ERROR_TO_SDR_PARSE_ERRNUM (ctx, obj_sdr_record_header);
          goto cleanup;
        }
      *record_type = val;
    }

  rv = 0;
  ctx->errnum = IPMI_SDR_PARSE_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_sdr_record_header);
  return (rv);
}
