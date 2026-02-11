sftk_DestroySession(SFTKSession *session)
{
    SFTKObjectList *op,*next;
    PORT_Assert(session->refCount == 0);


    for (op = session->objects[0]; op != NULL; op = next) {
        next = op->next;

	op->next = op->prev = NULL;
	sftk_DeleteObject(session,op->parent);
    }
    PZ_DestroyLock(session->objectLock);
    if (session->enc_context) {
	sftk_FreeContext(session->enc_context);
    }
    if (session->hash_context) {
	sftk_FreeContext(session->hash_context);
    }
    if (session->sign_context) {
	sftk_FreeContext(session->sign_context);
    }
    if (session->search) {
	sftk_FreeSearch(session->search);
    }
    PORT_Free(session);
}
