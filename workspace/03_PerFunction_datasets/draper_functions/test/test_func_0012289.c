bp__page_save_value(bp_db_t* t,
                        bp__page_t* page,
                        const uint64_t index,
                        const int cmp,
                        const bp_key_t* key,
                        const bp_value_t* value,
                        bp_update_cb update_cb,
                        void* arg) {
  int ret;
  bp__kv_t previous, tmp;


  if (cmp == 0) {

    if (update_cb != NULL) {
      bp_value_t prev_value;

      ret = bp__page_load_value(t, page, index, &prev_value);
      if (ret != BP_OK) return ret;

      ret = update_cb(arg, &prev_value, value);
      free(prev_value.value);

      if (!ret) return BP_EUPDATECONFLICT;
    }
    previous.offset = page->keys[index].offset;
    previous.length = page->keys[index].config;
    bp__page_remove_idx(t, page, index);
  }


  tmp.value = key->value;
  tmp.length = key->length;


  ret = bp__value_save(t,
                       value,
                       cmp == 0 ? &previous : NULL,
                       &tmp.offset,
                       &tmp.config);
  if (ret != BP_OK) return ret;


  bp__page_shiftr(t, page, index);


  ret = bp__kv_copy(&tmp, &page->keys[index], 1);
  if (ret != BP_OK) {

    bp__page_shiftl(t, page, index);
    return ret;
  }

  page->byte_size += BP__KV_SIZE(tmp);
  page->length++;

  return BP_OK;
}
