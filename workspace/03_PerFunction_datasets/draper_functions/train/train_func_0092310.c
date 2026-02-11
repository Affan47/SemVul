ipmi_sdr_cache_search_record_id (ipmi_sdr_cache_ctx_t ctx, uint16_t record_id)
{
  off_t offset;
  int found = 0;

  if (!ctx || ctx->magic != IPMI_SDR_CACHE_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_sdr_cache_ctx_errormsg (ctx), ipmi_sdr_cache_ctx_errnum (ctx));
      return (-1);
    }

  if (ctx->operation != IPMI_SDR_CACHE_OPERATION_READ_CACHE)
    {
      SDR_CACHE_SET_ERRNUM (ctx, IPMI_SDR_CACHE_ERR_CACHE_READ_INITIALIZATION);
      return (-1);
    }

  offset = ctx->records_start_offset;
  while (offset < ctx->file_size)
    {
      uint8_t *ptr = ctx->sdr_cache + offset;
      uint16_t record_id_current;
      unsigned int record_length;


      record_id_current = (uint16_t)ptr[IPMI_SDR_CACHE_SDR_RECORD_ID_INDEX_LS] & 0xFF;
      record_id_current |= ((uint16_t)ptr[IPMI_SDR_CACHE_SDR_RECORD_ID_INDEX_MS] & 0xFF) << 8;

      if (record_id == record_id_current)
        {
          found++;
          ctx->current_offset = offset;
          break;
        }

      record_length = (uint8_t)((ctx->sdr_cache + offset)[IPMI_SDR_CACHE_SDR_RECORD_LENGTH_INDEX]);
      offset += IPMI_SDR_CACHE_SDR_RECORD_HEADER_LENGTH;
      offset += record_length;
    }

  if (!found)
    {
      SDR_CACHE_SET_ERRNUM (ctx, IPMI_SDR_CACHE_ERR_NOT_FOUND);
      return (-1);
    }

  ctx->errnum = IPMI_SDR_CACHE_ERR_SUCCESS;
  return (0);
}
