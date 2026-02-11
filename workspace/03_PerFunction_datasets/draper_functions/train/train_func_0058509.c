tfscan_print_hits(AjPList *l,
			      ajint hits, AjPReport outf,
			      const AjPTable t,
			      const AjPSeq seq, ajuint minlength,
			      const  AjPTable btable)
{
    ajint i;
    EmbPMatMatch m;
    const AjPStr acc = NULL;
    const AjPStr bf  = NULL;
    AjPFeattable ftable = NULL;
    AjPFeature gf  = NULL;
    AjPStr type = ajStrNewC("SO:0000235");
    AjPStr tmpstr = NULL;

    ftable = ajFeattableNewSeq(seq);


    for(i=0;i<hits;++i)
    {
	ajListPop(*l,(void **)&m);
	acc = ajTableFetchS(t, m->seqname);

	if(m->len >= minlength)
        {


            if(m->forward)
                gf = ajFeatNew(ftable, ajUtilGetProgram(), type,
                               m->start,
                               m->start+m->len-1,
                               (float) m->score,
                               '+',0);
            else
                gf = ajFeatNew(ftable, ajUtilGetProgram(), type,
                               m->start,
                               m->start+m->len-1,
                               (float) m->score,
                               '-',0);
            ajFmtPrintS(&tmpstr, "*acc %S", acc);
            ajFeatTagAddSS(gf, NULL, tmpstr);
            bf  = ajTableFetchS(btable, m->seqname);
            ajFmtPrintS(&tmpstr, "*factor %S", bf);
            ajFeatTagAddSS(gf, NULL, tmpstr);
        }

	embMatMatchDel(&m);
    }

    ajReportWrite(outf, ftable, seq);
    ajFeattableDel(&ftable);
    ajStrDel(&tmpstr);
    ajStrDel(&type);

    return;
}
