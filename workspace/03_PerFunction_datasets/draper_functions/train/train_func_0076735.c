TransDelete(TransObj *tobj)
{
    if(tobj == NULL) {
	return;
    }
    if(tobj->magic != TRANSMAGIC) {
	OOGLWarn("Internal warning: TransDelete'ing non-TransObj %x (%x != %x)",
	    tobj, tobj->magic, TRANSMAGIC);
	return;
    }
    if(tobj != NULL && RefDecr((Ref *)tobj) <= 0) {
	FREELIST_FREE(TransObj, tobj);
    }
}
