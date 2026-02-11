lGetChar(const lListElem *ep, int name)
{
   int pos;
   DENTER(CULL_BASIS_LAYER, "lGetChar");
   pos = lGetPosViaElem(ep, name, SGE_DO_ABORT);

   if (mt_get_type(ep->descr[pos].mt) != lCharT)
      incompatibleType2(MSG_CULL_GETCHAR_WRONGTYPEFORFIELDXY_SS , lNm2Str(name), multitypes[mt_get_type(ep->descr[pos].mt)]);
   DEXIT;
   return ep->cont[pos].c;
}
