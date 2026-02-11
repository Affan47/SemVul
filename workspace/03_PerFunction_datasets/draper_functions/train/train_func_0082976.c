SearchCorrespondQr(const Quadruple *tailQr,
		   int        entry)
{
    const Quadruple *pQr = tailQr;

    while(pQr != NULL){
	if(pQr->op[0]->kind == KIND_TEMP && pQr->op[0]->entry == entry){
	    break;
	}
	pQr = pQr->prev;
    }
    return(pQr);
}
