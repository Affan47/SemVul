__nss_cdb_dobyname(struct nss_cdb *dbp, const char *key, unsigned len,
                   void *result, char *buf, size_t bufl, int *errnop) {
  int r;

  if ((r = cdb_find(&dbp->cdb, key, len)) < 0)
    return *errnop = errno, NSS_STATUS_UNAVAIL;
  len = cdb_datalen(&dbp->cdb);
  if (!r || len < 2)
    return *errnop = ENOENT, NSS_STATUS_NOTFOUND;
  if (len >= bufl)
    return *errnop = ERANGE, NSS_STATUS_TRYAGAIN;
  if (cdb_read(&dbp->cdb, buf, len, cdb_datapos(&dbp->cdb)) != 0)
    return *errnop = errno, NSS_STATUS_UNAVAIL;
  buf[len] = '\0';
  if ((r = dbp->parsefn(result, buf, bufl)) < 0)
    return *errnop = ENOENT, NSS_STATUS_NOTFOUND;
  if (!r)
    return *errnop = ERANGE, NSS_STATUS_TRYAGAIN;

  return NSS_STATUS_SUCCESS;
}
