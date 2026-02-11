luaA_packresults (void)
{
  luaV_pack(L->Cstack.lua2C, L->Cstack.num, L->stack.top);
  incr_top;
}
