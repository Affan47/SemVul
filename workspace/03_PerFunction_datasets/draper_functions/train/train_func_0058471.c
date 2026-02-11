ipmi_sdr_parse_accuracy (ipmi_sdr_parse_ctx_t ctx,
                          const void *sdr_record,
                          unsigned int sdr_record_len,
                          double **accuracy)
{
  fiid_obj_t obj_sdr_record = NULL;
  uint32_t acceptable_record_types;
  uint16_t accuracy_raw;
  uint8_t accuracy_ls, accuracy_ms, accuracy_exp;
  double *tmp_accuracy = NULL;
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

  if (accuracy)
    *accuracy = NULL;

  acceptable_record_types = IPMI_SDR_PARSE_RECORD_TYPE_FULL_SENSOR_RECORD;

  if (!(obj_sdr_record = _sdr_record_get_common (ctx,
                                                 sdr_record,
                                                 sdr_record_len,
                                                 acceptable_record_types)))
    goto cleanup;

  if (accuracy)
    {
      double reading;

      if (FIID_OBJ_GET (obj_sdr_record,
                        "accuracy_ls",
                        &val) < 0)
        {
          SDR_PARSE_FIID_OBJECT_ERROR_TO_SDR_PARSE_ERRNUM (ctx, obj_sdr_record);
          goto cleanup;
        }
      accuracy_ls = val;

      if (FIID_OBJ_GET (obj_sdr_record,
                        "accuracy_ms",
                        &val) < 0)
        {
          SDR_PARSE_FIID_OBJECT_ERROR_TO_SDR_PARSE_ERRNUM (ctx, obj_sdr_record);
          goto cleanup;
        }
      accuracy_ms = val;


      accuracy_raw = accuracy_ls | (((uint16_t)accuracy_ms) << 6);

      if (FIID_OBJ_GET (obj_sdr_record,
                        "accuracy_exp",
                        &val) < 0)
        {
          SDR_PARSE_FIID_OBJECT_ERROR_TO_SDR_PARSE_ERRNUM (ctx, obj_sdr_record);
          goto cleanup;
        }
      accuracy_exp = val;

      if (ipmi_sensor_decode_accuracy (accuracy_raw,
                                       accuracy_exp,
                                       &reading) < 0)
        {
          SDR_PARSE_SET_ERRNUM (ctx, IPMI_SDR_PARSE_ERR_INTERNAL_ERROR);
          goto cleanup;
        }

      if (!(tmp_accuracy = (double *)malloc (sizeof (double))))
        {
          SDR_PARSE_SET_ERRNUM (ctx, IPMI_SDR_PARSE_ERR_OUT_OF_MEMORY);
          goto cleanup;
        }
      (*tmp_accuracy) = reading;
    }

  if (accuracy)
    *accuracy = tmp_accuracy;

  rv = 0;
  ctx->errnum = IPMI_SDR_PARSE_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_sdr_record);
  if (rv < 0)
    free (tmp_accuracy);
  return (rv);
}
