destroy_misc_data(struct pivot_desc* pv,
                              struct http_request* self) {
  u32 i;

  for (i=0;i<MISC_ENTRIES;i++) {

    if (pv->misc_req[i] != self) {

      if (pv->misc_req[i])
        destroy_request(pv->misc_req[i]);

      if (pv->misc_res[i])
        destroy_response(pv->misc_res[i]);

    }

    pv->misc_req[i] = NULL;
    pv->misc_res[i] = NULL;

  }

  pv->misc_cnt = 0;

}
