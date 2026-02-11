lr_gen(p_wf,ctx)
p_wf_t p_wf;
uword  ctx;
{
 unqpos_t next_pos;
 mess_t   next_mes;
 long     prev_no;
 long     next_no;
 bool     ingap;
 long     context=ctx;


 if (context==CTXINF) context=MAXLINES;


 wf_wr(p_wf,"\nGlobal Local| Input File\n");
 wf_dup(p_wf,'-',(ulong) 12); wf_wr(p_wf,"+");
 wf_dup(p_wf,'-',(ulong) (LISTWIDTH-13)); wf_wr(p_wf,"\n");


 ls_fir(line_list);
 tb_fir(p_msgtab);


 ingap=FALSE; prev_no = -(context+1);
 if (tb_rea(p_msgtab,PV &next_pos,PV &next_mes))
    next_no=next_pos.up_pos.ps_line;
 else
    next_no=MAXLINES+context+1;

 while (TRUE)
   {
    ln_t *p_line;


    ls_nxt(line_list,PPV &p_line);
    if (p_line==NULL) break;


    if ((((long) p_line->ln_global) <= prev_no+context) ||
        (((long) p_line->ln_global) >= next_no-context))
       {line_wri(p_wf,p_line);ingap=FALSE;}
    else
       if (!ingap)
          {wf_wr(p_wf,".................\n");ingap=TRUE;}


    while (next_no == p_line->ln_global)
      {

       mess_wri(p_wf,&next_mes,(uword) 0,
                (uword) next_pos.up_pos.ps_column);


       prev_no=next_no;
       if (tb_rea(p_msgtab,PV &next_pos,PV &next_mes))
          next_no=next_pos.up_pos.ps_line;
       else
          next_no=MAXLINES+context+1;
      }
   }


 {bool result;
  result=tb_rea(p_msgtab,PV &next_pos,PV &next_mes);
  as_cold(!result,
          "lr_gen: Messages remaining in message table after listing.");
 }


 wf_dup(p_wf,'-',(ulong) 12); wf_wr(p_wf,"+");
 wf_dup(p_wf,'-',(ulong) (LISTWIDTH-13)); wf_wr(p_wf,"\n");
 wf_wl(p_wf,"");
}
