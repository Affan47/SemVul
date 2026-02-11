extract_apnd_uid(mailimap * session,
    uint32_t * uidvalidity_result,
    struct mailimap_set ** result)
{
  clistiter * cur;

  * uidvalidity_result = 0;
  * result = NULL;

  if (session->imap_response_info == NULL) {
    return;
  }

  for(cur = clist_begin(session->imap_response_info->rsp_extension_list) ;
      cur != NULL ; cur = clist_next(cur)) {
    struct mailimap_extension_data * ext_data;
    struct mailimap_uidplus_resp_code_apnd * resp_code_apnd;

    ext_data = clist_content(cur);
    if (ext_data->ext_extension != &mailimap_extension_uidplus)
      continue;

    if (ext_data->ext_type != MAILIMAP_UIDPLUS_RESP_CODE_APND)
      continue;

    resp_code_apnd = ext_data->ext_data;

    * uidvalidity_result = resp_code_apnd->uid_uidvalidity;
    * result = resp_code_apnd->uid_set;
    resp_code_apnd->uid_set = NULL;
    break;
  }
}
