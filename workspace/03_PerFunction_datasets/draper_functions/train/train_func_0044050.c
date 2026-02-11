prepare_keybuf(const cmd_exec_args& args, uchar *key_buf, TABLE *table,
  KEY& kinfo, size_t invalues_index)
{
  size_t kplen_sum = 0;
  DBG_KEY(fprintf(stderr, "SLOW\n"));
  for (size_t i = 0; i < args.kvalslen; ++i) {
    const KEY_PART_INFO & kpt = kinfo.key_part[i];
    string_ref kval = args.kvals[i];
    if (args.invalues_keypart >= 0 &&
      static_cast<size_t>(args.invalues_keypart) == i) {
      kval = args.invalues[invalues_index];
    }
    if (kval.begin() == 0) {
      kpt.field->set_null();
    } else {
      kpt.field->set_notnull();
    }
    kpt.field->store(kval.begin(), kval.size(), &my_charset_bin);
    kplen_sum += kpt.store_length;
    DBG_KEYLEN(fprintf(stderr, "l=%u sl=%zu\n", kpt.length,
      kpt.store_length));
  }
  key_copy(key_buf, table->record[0], &kinfo, kplen_sum);
  DBG_KEYLEN(fprintf(stderr, "sum=%zu flen=%u\n", kplen_sum,
    kinfo.key_length));
  return kplen_sum;
}
