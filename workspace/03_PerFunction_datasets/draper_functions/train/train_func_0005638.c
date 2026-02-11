kinit()
{
  atexit(finally);
  I i;
  PG = sysconf(_SC_PAGE_SIZE);
  if(PG&(PG-1)){er(Pagesize not power of 2); exit(1);}

  DT_SIZE                 = DT_OFFSET(TABLE_END);
  DT_END_OFFSET           = DT_OFFSET(end);
  DT_ADVERB_OFFSET        = DT_OFFSET(over);
  DT_VERB_OFFSET          = DT_OFFSET(flip);
  DT_SPECIAL_VERB_OFFSET  = DT_OFFSET(_0m);

  offsetOver      = DT_OFFSET(over);
  offsetScan      = DT_OFFSET(scan);
  offsetEach      = DT_OFFSET(each);
  offsetEachright = DT_OFFSET(eachright);
  offsetEachleft  = DT_OFFSET(eachleft);
  offsetEachpair  = DT_OFFSET(eachpair);


  offsetWhat  = DT_OFFSET(what);
  offsetAt    = DT_OFFSET(at);
  offsetDot   = DT_OFFSET(dot);
  offsetColon = DT_OFFSET(colon_dyadic);
  offsetSSR   = DT_OFFSET(_ssr);

  kerr("undescribed");
  SYMBOLS=newN();
  seedPRNG(randomBits());
  KFIXED=newK(0,0); kap(&KFIXED,NIL=Kn());cd(NIL);
  __d = sp(".k"); LS=sp(""); DO(3,IFP[i]=sp(IFS[i]))
#ifdef DEBUG
  test();
#endif
  KTREE=Kd();
  K x;
  kap(&KTREE,x=newEntry(sp("k"))); cd(x);
  kap(&KTREE,x=newE(sp("t"),_dot_t())); cd(x);

  R 0;
}
