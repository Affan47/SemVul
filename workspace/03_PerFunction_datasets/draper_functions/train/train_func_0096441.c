init_hash(hashp, file, info)
	HTAB *hashp;
	const char *file;
	const HASHINFO *info;
{
#ifdef _STATBUF_ST_BLKSIZE
	struct stat statbuf;
#endif
	int nelem;

	nelem = 1;
	hashp->NKEYS = 0;
	hashp->LORDER = BYTE_ORDER;
	hashp->BSIZE = DEF_BUCKET_SIZE;
	hashp->BSHIFT = DEF_BUCKET_SHIFT;
	hashp->SGSIZE = DEF_SEGSIZE;
	hashp->SSHIFT = DEF_SEGSIZE_SHIFT;
	hashp->DSIZE = DEF_DIRSIZE;
	hashp->FFACTOR = DEF_FFACTOR;
	hashp->hash = __default_hash;
	memset(hashp->SPARES, 0, sizeof(hashp->SPARES));
	memset(hashp->BITMAPS, 0, sizeof (hashp->BITMAPS));


#ifdef _STATBUF_ST_BLKSIZE
	if (file != NULL) {
		if (stat(file, &statbuf))
			return (NULL);
		hashp->BSIZE = statbuf.st_blksize;
		hashp->BSHIFT = __hash_log2(hashp->BSIZE);
	}
#endif

	if (info) {
		if (info->bsize) {

			hashp->BSHIFT = __hash_log2(info->bsize);
			hashp->BSIZE = 1 << hashp->BSHIFT;
			if (hashp->BSIZE > MAX_BSIZE) {
				errno = EINVAL;
				return (NULL);
			}
		}
		if (info->ffactor)
			hashp->FFACTOR = info->ffactor;
		if (info->hash)
			hashp->hash = info->hash;
		if (info->nelem)
			nelem = info->nelem;
		if (info->lorder) {
			if (info->lorder != BIG_ENDIAN &&
			    info->lorder != LITTLE_ENDIAN) {
				errno = EINVAL;
				return (NULL);
			}
			hashp->LORDER = info->lorder;
		}
	}

	if (init_htab(hashp, nelem))
		return (NULL);
	else
		return (hashp);
}
