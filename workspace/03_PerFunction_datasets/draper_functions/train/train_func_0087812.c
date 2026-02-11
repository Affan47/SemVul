gset(void *p1, void *val, int n, int typ)
{ if (val==0)
    val = aet_types[typ].dflt;
    switch (typ){

#define GSET(p,n,typ,val) {typ x = *((typ *) val); GSET1(p,n,typ,x)}
#define GSET1(p,n,typ,val) while (n-- > 0) \
      { *((typ *) p) = val; \
	  p = p + sizeof(typ); \
	  } break;

    case aet_object: GSET(p1,n,object,val);
    case aet_ch:     GSET(p1,n,char,val);

    case aet_bit:    GSET(p1,n,fixnum,val);
    case aet_fix:    GSET(p1,n,fixnum,val);
    case aet_sf:     GSET(p1,n,shortfloat,val);
    case aet_lf:     GSET(p1,n,longfloat,val);
    case aet_char:   GSET(p1,n,char,val);
    case aet_uchar:  GSET(p1,n,unsigned char,val);
    case aet_short:  GSET(p1,n,short,val);
    case aet_ushort: GSET(p1,n,unsigned short,val);
    default:         FEerror("bad elttype",0);
    }
  }
