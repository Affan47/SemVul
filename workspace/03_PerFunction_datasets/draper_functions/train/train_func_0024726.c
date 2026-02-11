plD_state_plm(PLStream *pls, PLINT op)
{
    U_CHAR c = (U_CHAR) CHANGE_STATE;
    int i;

    dbug_enter("plD_state_plm");

    plm_wr( pdf_wr_1byte(pls->pdfs, c) );
    plm_wr( pdf_wr_1byte(pls->pdfs, op) );

    switch (op) {

    case PLSTATE_WIDTH:
	plm_wr( pdf_wr_2bytes(pls->pdfs, (U_SHORT) (pls->width)) );
	break;

    case PLSTATE_COLOR0:
	plm_wr( pdf_wr_2bytes(pls->pdfs, (short) pls->icol0) );

	if (pls->icol0 == PL_RGB_COLOR) {
	    plm_wr( pdf_wr_1byte(pls->pdfs, pls->curcolor.r) );
	    plm_wr( pdf_wr_1byte(pls->pdfs, pls->curcolor.g) );
	    plm_wr( pdf_wr_1byte(pls->pdfs, pls->curcolor.b) );
	}
	break;

    case PLSTATE_COLOR1:
	plm_wr( pdf_wr_2bytes(pls->pdfs, (U_SHORT) pls->icol1) );
	break;

    case PLSTATE_FILL:
	plm_wr( pdf_wr_1byte(pls->pdfs, (U_CHAR) pls->patt) );
	break;

    case PLSTATE_CMAP0:
	plm_wr( pdf_wr_2bytes(pls->pdfs, (U_SHORT) pls->ncol0) );
	for (i = 0; i < pls->ncol0; i++) {
	    plm_wr( pdf_wr_1byte(pls->pdfs, pls->cmap0[i].r) );
	    plm_wr( pdf_wr_1byte(pls->pdfs, pls->cmap0[i].g) );
	    plm_wr( pdf_wr_1byte(pls->pdfs, pls->cmap0[i].b) );
	}
	break;

    case PLSTATE_CMAP1:
	plm_wr( pdf_wr_2bytes(pls->pdfs, (U_SHORT) pls->ncol1) );
	for (i = 0; i < pls->ncol1; i++) {
	    plm_wr( pdf_wr_1byte(pls->pdfs, pls->cmap1[i].r) );
	    plm_wr( pdf_wr_1byte(pls->pdfs, pls->cmap1[i].g) );
	    plm_wr( pdf_wr_1byte(pls->pdfs, pls->cmap1[i].b) );
	}
	break;
    }
}
