_parse_type_length (ipmi_fru_parse_ctx_t ctx,
                    const void *areabuf,
                    unsigned int areabuflen,
                    unsigned int current_area_offset,
                    uint8_t *number_of_data_bytes,
                    ipmi_fru_parse_field_t *field)
{
  const uint8_t *areabufptr = areabuf;
  uint8_t type_length;
  uint8_t type_code;

  assert (ctx);
  assert (ctx->magic == IPMI_FRU_PARSE_CTX_MAGIC);
  assert (areabuf);
  assert (areabuflen);
  assert (number_of_data_bytes);

  type_length = areabufptr[current_area_offset];


  assert (type_length != IPMI_FRU_SENTINEL_VALUE);

  type_code = (type_length & IPMI_FRU_TYPE_LENGTH_TYPE_CODE_MASK) >> IPMI_FRU_TYPE_LENGTH_TYPE_CODE_SHIFT;
  (*number_of_data_bytes) = type_length & IPMI_FRU_TYPE_LENGTH_NUMBER_OF_DATA_BYTES_MASK;


  if (type_code == IPMI_FRU_TYPE_LENGTH_TYPE_CODE_LANGUAGE_CODE
      && (*number_of_data_bytes) == 0x01)
    {
      FRU_PARSE_SET_ERRNUM (ctx, IPMI_FRU_PARSE_ERR_FRU_INFORMATION_INCONSISTENT);
      return (-1);
    }

  if ((current_area_offset + 1 + (*number_of_data_bytes)) > areabuflen)
    {
      FRU_PARSE_SET_ERRNUM (ctx, IPMI_FRU_PARSE_ERR_FRU_INFORMATION_INCONSISTENT);
      return (-1);
    }

  if (field)
    {
      memset (field->type_length_field,
              '\0',
              IPMI_FRU_PARSE_AREA_TYPE_LENGTH_FIELD_MAX);
      memcpy (field->type_length_field,
              &areabufptr[current_area_offset],
              1 + (*number_of_data_bytes));
      field->type_length_field_length = 1 + (*number_of_data_bytes);
    }

  return (0);
}
