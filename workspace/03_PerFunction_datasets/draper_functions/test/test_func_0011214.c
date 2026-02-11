xeqtrc(C *str,I x){
  if(dbg_hold)R 0;
  DH("\343%s%s%s execute of string [%s%s\n",
     dbg_pfx(),(x&1)?"Entering":"Exiting",(x&2)?" protected":"",
     (40<strlen(str))?"<too long>":str,x?"] . . .":"]");
  FFL;
  if(dbg_cbfunc)
    {
      dbg_callcb("xeq",2,
		 (A)gsv(0,str),
		 ge(MS(si(blurb[(x&1)?0:1]))),
		 (A)0);
    }

  R -1;
}
