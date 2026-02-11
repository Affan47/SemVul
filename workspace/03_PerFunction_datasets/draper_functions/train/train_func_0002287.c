updateName_WOSD(XMLSTR lpszName)
{
    if (!d) { free(lpszName); return NULL; }
    if (d->lpszName&&(lpszName!=d->lpszName)) free((void*)d->lpszName);
    d->lpszName=lpszName;
    return lpszName;
}
