param_numerical_start(struct pivot_desc* pv) {
  u8 *val = TPAR(pv->req), *out, fmt[16];
  u32 i, dig, tail;
  s32 val_i, range_st, range_en;
  u8  zero_padded = 0;

  DEBUG_HELPER(pv);

  if (!descendants_ok(pv)) goto schedule_next;


  i = 0;
  while (val[i] && !isdigit(val[i])) i++;
  if (!val[i]) goto schedule_next;

  dig = i;
  while (val[i] && isdigit(val[i])) i++;
  tail = i;


  if (tail - dig > PAR_MAX_DIGITS) goto schedule_next;

  if (val[dig] == '0' && tail - dig > 1) zero_padded = 1;

  val_i = atoi((char*)val + dig);
  range_st = val_i - PAR_INT_FUZZ;
  range_en = val_i + PAR_INT_FUZZ;
  if (range_st < 0) range_st = 0;

  if (zero_padded) sprintf((char*)fmt, "%%.%us%%0%uu%%s", dig, tail - dig);
  else sprintf((char*)fmt, "%%.%us%%%uu%%s", dig, tail - dig);

  out = ck_alloc(strlen((char*)val) + 16);


  pv->state = PSTATE_PAR_NUMBER;

  pv->num_pending = range_en - range_st + 1;

  for (i=range_st;i<=range_en;i++) {
    struct http_request* n;

    if (i == val_i) { pv->num_pending--; continue; }

    sprintf((char*)out, (char*)fmt, val, i, val + tail);

    n = req_copy(pv->req, pv, 1);
    ck_free(TPAR(n));
    TPAR(n) = ck_strdup((u8*)out);
    n->callback = param_numerical_check;
    async_request(n);

  }

  ck_free(out);

  if (!pv->num_pending) goto schedule_next;
  return;

schedule_next:

  pv->state = PSTATE_PAR_DICT;
  param_dict_start(pv);


}
