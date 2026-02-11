wv_elin(p_el)

p_el_t p_el;
{
 p_bp_t p_bp;
 p_ma_t p_ma = p_el->el_p_mac;
 p_md_t p_md = &p_ma->ma_defn[p_ma->ma_minlev];

 as_cold(p_el->el_kind==EL_INVC,"wv_elin: Not an invocation.");


 ls_loo(p_md->md_body,1L,PPV &p_bp);

 wf_wr(&f_t,"<A HREF=\"#");
 wf_dec(&f_t,(ulong) p_bp->bp_seq);
 wf_wr(&f_t,"\">");
 wv_ugstr(p_ma->ma_name,EOL_BR_NO);
 wf_wr(&f_t,"</A>");


 if (ls_len(p_el->el_parls) > 0)
   {
    ulong    parnum;
    wf_wr(&f_t,"<FONT COLOR=#CC0033>(</FONT>");
    ls_fir(p_el->el_parls);
    ls_fir(p_el->el_pretx);
    ls_fir(p_el->el_postx);
    parnum=1;
    while (TRUE)
      {
       p_ells_t *pp_exp;
       p_scls_t *pp_scls1;
       p_scls_t *pp_scls2;
       ls_nxt(p_el->el_parls,PPV &pp_exp);
       ls_nxt(p_el->el_pretx,PPV &pp_scls1);
       ls_nxt(p_el->el_postx,PPV &pp_scls2);
       if (pp_exp==NULL) break;
       if (parnum++ > 1) wf_wr(&f_t,"<FONT COLOR=#CC0033>,</FONT>");
       wv_verb(*pp_scls1);
       wf_wr(&f_t,"<FONT COLOR=#CC0033>\"</FONT>");
       wv_ex(*pp_exp);
       wf_wr(&f_t,"<FONT COLOR=#CC0033>\"</FONT>");
       wv_verb(*pp_scls2);
      }
    wf_wr(&f_t,"<FONT COLOR=#CC0033>)</FONT>");
   }
}
