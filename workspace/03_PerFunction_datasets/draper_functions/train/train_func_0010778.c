encseq_lua_create_reader_with_readmode(lua_State *L)
{
  GtEncseq **encseq;
  GtEncseqReader *reader;
  unsigned long startpos;
  GtReadmode readmode;
  encseq = check_encseq(L, 1);
  readmode = luaL_checknumber(L, 2);
  startpos = luaL_checknumber(L, 3);
  luaL_argcheck(L, startpos < gt_encseq_total_length(*encseq), 3,
                "cannot exceed total length of encoded sequence");
  reader = gt_encseq_create_reader_with_readmode(*encseq, readmode, startpos);
  gt_assert(reader);
  gt_lua_encseq_reader_push(L, reader);
  return 1;
}
