NSC_FindObjectsFinal(CK_SESSION_HANDLE hSession)
{
    SFTKSession *session;
    SFTKSearchResults *search;

    CHECK_FORK();

    session = sftk_SessionFromHandle(hSession);
    if (session == NULL) return CKR_SESSION_HANDLE_INVALID;
    search = session->search;
    session->search = NULL;
    sftk_FreeSession(session);
    if (search != NULL) {
	sftk_FreeSearch(search);
    }
    return CKR_OK;
}
