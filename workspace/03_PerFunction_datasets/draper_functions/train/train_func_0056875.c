getAttributeValue(SessionHandleSuffix suffix,
    CK_OBJECT_HANDLE hObject, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount)
{
    refreshTokenState();

    if( ! isValidSession(suffix) ) {
        throw PKCS11Exception(CKR_SESSION_HANDLE_INVALID);
    }

    ObjectConstIter iter = find_if(tokenObjects.begin(), tokenObjects.end(),
        ObjectHandleMatch(hObject));

    if( iter == tokenObjects.end() ) {
        throw PKCS11Exception(CKR_OBJECT_HANDLE_INVALID);
    }

    iter->getAttributeValue(pTemplate, ulCount, log);
}
