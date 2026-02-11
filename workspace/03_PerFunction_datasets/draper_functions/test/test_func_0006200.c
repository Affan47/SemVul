sftk_TLSPRFHashDestroy(TLSPRFContext *cx, PRBool freeit)
{
    if (freeit) {
	if (cx->cxBufPtr != cx->cxBuf)
	    PORT_ZFree(cx->cxBufPtr, cx->cxBufSize);
	PORT_ZFree(cx, cx->cxSize);
    }
}
