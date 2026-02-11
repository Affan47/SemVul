sel_parse_get_record_header_info (ipmi_sel_parse_ctx_t ctx,
                                  struct ipmi_sel_parse_entry *sel_parse_entry,
                                  uint16_t *record_id,
                                  uint8_t *record_type)
{
  fiid_obj_t obj_sel_record_header = NULL;
  uint64_t val;
  int rv = -1;

  assert (ctx);
  assert (ctx->magic == IPMI_SEL_PARSE_CTX_MAGIC);
  assert (sel_parse_entry);
  assert (record_id || record_type);

  if (sel_parse_entry->sel_event_record_len < IPMI_SEL_RECORD_HEADER_LENGTH)
    {
      ctx->errnum = IPMI_SEL_PARSE_ERR_INVALID_SEL_ENTRY;
      goto cleanup;
    }

  if (!(obj_sel_record_header = fiid_obj_create (tmpl_sel_record_header)))
    {
      SEL_PARSE_ERRNO_TO_SEL_PARSE_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (fiid_obj_set_all (obj_sel_record_header,
                        sel_parse_entry->sel_event_record,
                        sel_parse_entry->sel_event_record_len) < 0)
    {
      SEL_PARSE_FIID_OBJECT_ERROR_TO_SEL_PARSE_ERRNUM (ctx, obj_sel_record_header);
      goto cleanup;
    }

  if (record_id)
    {
      if (FIID_OBJ_GET (obj_sel_record_header,
                        "record_id",
                        &val) < 0)
        {
          SEL_PARSE_FIID_OBJECT_ERROR_TO_SEL_PARSE_ERRNUM (ctx, obj_sel_record_header);
          goto cleanup;
        }
      (*record_id) = val;
    }

  if (record_type)
    {
      if (FIID_OBJ_GET (obj_sel_record_header,
                        "record_type",
                        &val) < 0)
        {
          SEL_PARSE_FIID_OBJECT_ERROR_TO_SEL_PARSE_ERRNUM (ctx, obj_sel_record_header);
          goto cleanup;
        }
      (*record_type) = val;

      if (ctx->flags & IPMI_SEL_PARSE_FLAGS_ASSUME_SYTEM_EVENT_RECORDS
	  && !IPMI_SEL_RECORD_TYPE_VALID ((*record_type)))
	(*record_type) = IPMI_SEL_RECORD_TYPE_SYSTEM_EVENT_RECORD;
    }

  rv = 0;
 cleanup:
  fiid_obj_destroy (obj_sel_record_header);
  return (rv);
}
