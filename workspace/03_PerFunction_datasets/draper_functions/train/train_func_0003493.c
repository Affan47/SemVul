releaseIdentifierInfo(IdentifierInfo *idInfo) const {
    if (idInfo != NULL) {
        SpoofImpl *nonConstThis = const_cast<SpoofImpl *>(this);
        {
            Mutex m;
            if (nonConstThis->fCachedIdentifierInfo == NULL) {
                nonConstThis->fCachedIdentifierInfo = idInfo;
                idInfo = NULL;
            }
        }
        delete idInfo;
    }
}
