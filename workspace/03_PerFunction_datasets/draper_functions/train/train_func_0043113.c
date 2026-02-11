dm_macro(p_wf,p_ma)

p_wf_t p_wf;
p_ma_t p_ma;
{
 wf_wl(p_wf,"");
 centerln(p_wf,DUMP_WIDTH-20,'-',"Start of Macro Dump");


 sprintf(linet1,"Macro Name  : \"%s\"",p_ma->ma_name); wf_wl(p_wf,linet1);
 sprintf(linet1,"Macro MinLv : %u",(unsigned) p_ma->ma_minlev); wf_wl(p_wf,linet1);


 {
  p_mc_t p_mc;
  ulong  mcnum;
  wf_wl(p_wf,"Call list   :");
  ls_fir(p_ma->ma_calls);
  ls_nxt(p_ma->ma_calls,PPV &p_mc);
  mcnum=1;
  while (p_mc != NULL)
    {
     sprintf(linet1,
 "   Call %lu: Parameters=%lu, Sequence num=%lu, Position(L,C)=(%lu,%lu).",
             (ulong) mcnum,
             (ulong) p_mc->mc_npar,
             (ulong) p_mc->mc_seq,
             (ulong) p_mc->mc_ps.ps_line,
             (ulong) p_mc->mc_ps.ps_column);
     wf_wl(p_wf,linet1);
     ls_nxt(p_ma->ma_calls,PPV &p_mc);
     mcnum++;
    }
 }


 {
  ubyte level;
  for (level=0; level<=MAXLIBLEV; level++)
     dm_maclv(p_wf,&p_ma->ma_defn[level],(ulong) level);
 }

 centerln(p_wf,DUMP_WIDTH-20,'-',"End of Macro Dump");
 wf_wl(p_wf,"");
}
