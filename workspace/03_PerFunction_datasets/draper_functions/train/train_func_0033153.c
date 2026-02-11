WritePageInfo(PLStream *pls, FPOS_T pp_offset)
{
    PLmDev *dev = (PLmDev *) pls->dev;
    FILE *file = pls->OutFile;
    int isfile = (pls->output_type == 0);
    U_CHAR c;
    FPOS_T cp_offset=0;


    if (isfile) {
	if (pl_fgetpos(file, &cp_offset))
	    plexit("WritePageInfo (plmeta.c): fgetpos call failed");

	UpdateIndex(pls, cp_offset);
    }


    if (dev->notfirst)
	c = BOP;
    else {
	c = BOP0;
	dev->notfirst = 1;
    }
    plm_wr( pdf_wr_1byte(pls->pdfs,  c) );
    plm_wr( pdf_wr_2bytes(pls->pdfs, (U_SHORT) pls->page) );
    plm_wr( pdf_wr_4bytes(pls->pdfs, (U_LONG) pp_offset) );
    plm_wr( pdf_wr_4bytes(pls->pdfs, (U_LONG) 0) );


    dev->lp_offset = cp_offset;


    plD_state_plm(pls, PLSTATE_COLOR0);
}
