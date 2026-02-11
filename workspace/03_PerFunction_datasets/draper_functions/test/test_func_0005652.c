D2Lreadgraph (int ioi, Tobj protograph) {
    graphframe_t *gframe, *tgframe;
    edgeframe_t *eframe, *teframe;
    Tobj graph;
    long m;

    protogo = protograph;
    nameo = Tstring ("name");
    m = Mpushmark (nameo);
    attro = Tstring ("attr");
    Mpushmark (attro);
    edgeso = Tstring ("edges");
    Mpushmark (edgeso);
    hporto = Tstring ("hport");
    Mpushmark (hporto);
    tporto = Tstring ("tport");
    Mpushmark (tporto);
    heado = Tstring ("head");
    Mpushmark (heado);
    tailo = Tstring ("tail");
    Mpushmark (tailo);
    yaccdone = FALSE;
    gstack = topgframe = NULL;
    errflag = FALSE;
    lex_begin (ioi);
    yyparse ();
    graph = NULL;
    if (topgframe) {
        graph = (errflag) ? NULL : topgframe->g;
        for (gframe = gstack; gframe; gframe = tgframe) {
            for (eframe = gframe->estack; eframe; eframe = teframe) {
                teframe = eframe->next;
                Mfree (eframe, M_BYTE2SIZE (sizeof (edgeframe_t)));
            }
            tgframe = gframe->next;
            Mfree (gframe, M_BYTE2SIZE (sizeof (graphframe_t)));
        }
        goto done;
    }
done:
    Mpopmark (m);
    return graph;
}
