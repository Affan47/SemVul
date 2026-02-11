defines(char * fname)
#else
defines(fname)
 char *fname ;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  int v; int maxt=(-1); char *t;
  {
    zzBLOCK(zztasp2);
    int zzcnt=1;
    zzMake0;
    {
    do {
      zzmatch(149); zzCONSUME;
      zzmatch(ID);
      t = mystrdup(LATEXT(1));
 zzCONSUME;

      zzmatch(INT);

      v = atoi(LATEXT(1));


			if ( ! isDLGmaxToken(t)) {
      TokenNum = v;
      if ( v>maxt ) maxt=v;
      if ( Tnum( t ) == 0 ) {
      addForcedTname( t, v );
    } else {
    warnFL(eMsg1("redefinition of token %s; ignored",t), fname,zzline);
  };
};
 zzCONSUME;

      zzLOOP(zztasp2);
    } while ( (LA(1)==149) );
    zzEXIT(zztasp2);
    }
  }
  TokenNum = maxt + 1;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd10, 0x8);
  }
}
