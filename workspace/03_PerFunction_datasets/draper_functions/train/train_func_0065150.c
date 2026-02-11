wv_ugsc(p_sc,eolbr)

p_sc_t p_sc;
bool   eolbr;
{
 char *p      = p_sc->sc_first;
 char *p_last = p_sc->sc_last;

 while (p<=p_last)
   {
    char ch = *p++;
    if ((ch == EOL) && seen_eol && (!eolbr))
       wf_wr(&f_t,"\n<P>");
    else
       wv_ugch(ch,eolbr);
    seen_eol = (ch == EOL);
   }
}
