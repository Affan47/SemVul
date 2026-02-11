wv_docnt()


{

 wv_head();


 tex_head(&f_t);

 ls_fir(document_list);
 literal=FALSE;
 while (TRUE)
   {
    p_dc_t p_dc;
    ls_nxt(document_list,PPV &p_dc);
    if (p_dc == NULL) break;
    wv_dc(p_dc);
   }
 wf_wl(&f_t,"\\bye");


 wv_tail();
}
