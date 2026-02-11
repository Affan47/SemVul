uriResolve(pBase, pObjRel)
    Uri *pBase;
    Tcl_Obj *pObjRel;
{
    char const *zScheme = pBase->zScheme;
    char const *zAuthority = pBase->zAuthority;
    char *zPath = pBase->zPath;
    char const *zQuery = pBase->zQuery;
    char const *zFragment = pBase->zFragment;

    char *zRes;
    Uri *pTmp = objToUri(pObjRel);

    if (pTmp->zScheme) {
        zScheme    = pTmp->zScheme;
        zAuthority = pTmp->zAuthority;
        zPath      = pTmp->zPath;
        zQuery     = pTmp->zQuery;
        zFragment  = pTmp->zFragment;
    }

    else if (pTmp->zAuthority) {
        zAuthority = pTmp->zAuthority;
        zPath      = pTmp->zPath;
        zQuery     = pTmp->zQuery;
        zFragment  = pTmp->zFragment;
    }

    else if (pTmp->zPath) {
        zPath      = combinePath(zPath, pTmp->zPath);
        zQuery     = pTmp->zQuery;
        zFragment  = pTmp->zFragment;
        cleanPath(zPath);
    }

    else if (pTmp->zQuery) {
        zQuery     = pTmp->zQuery;
        zFragment  = pTmp->zFragment;
    }

    else if (pTmp->zFragment) {
        zFragment  = pTmp->zFragment;
    }

    zRes = makeUri(zScheme, zAuthority, zPath, zQuery, zFragment);
    if (zPath != pBase->zPath && zPath != pTmp->zPath) {
        HtmlFree(zPath);
    }
    HtmlFree(pTmp);
    return zRes;
}
