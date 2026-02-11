lj_dispatch_init_hotcount(global_State *g)
{
  int32_t hotloop = G2J(g)->param[JIT_P_hotloop];
  HotCount start = (HotCount)(hotloop*HOTCOUNT_LOOP - 1);
  HotCount *hotcount = G2GG(g)->hotcount;
  uint32_t i;
  for (i = 0; i < HOTCOUNT_SIZE; i++)
    hotcount[i] = start;
}
