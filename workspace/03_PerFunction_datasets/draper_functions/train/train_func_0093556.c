add_cert_dir(BY_DIR *ctx, const char *dir, int type)
	{
	int j,len;
	const char *s,*ss,*p;

	if (dir == NULL || !*dir)
	    {
	    X509err(X509_F_ADD_CERT_DIR,X509_R_INVALID_DIRECTORY);
	    return 0;
	    }

	s=dir;
	p=s;
	do
		{
		if ((*p == LIST_SEPARATOR_CHAR) || (*p == '\0'))
			{
			BY_DIR_ENTRY *ent;
			ss=s;
			s=p+1;
			len=(int)(p-ss);
			if (len == 0) continue;
			for (j=0; j < sk_BY_DIR_ENTRY_num(ctx->dirs); j++)
				{
				ent = sk_BY_DIR_ENTRY_value(ctx->dirs, j);
				if (strlen(ent->dir) == (size_t)len &&
				    strncmp(ent->dir,ss,(unsigned int)len) == 0)
					break;
				}
			if (j < sk_BY_DIR_ENTRY_num(ctx->dirs))
				continue;
			if (ctx->dirs == NULL)
				{
				ctx->dirs = sk_BY_DIR_ENTRY_new_null();
				if (!ctx->dirs)
					{
					X509err(X509_F_ADD_CERT_DIR,ERR_R_MALLOC_FAILURE);
					return 0;
					}
				}
			ent = OPENSSL_malloc(sizeof(BY_DIR_ENTRY));
			if (!ent)
				return 0;
			ent->dir_type = type;
			ent->hashes = sk_BY_DIR_HASH_new(by_dir_hash_cmp);
			ent->dir = OPENSSL_malloc((unsigned int)len+1);
			if (!ent->dir || !ent->hashes)
				{
				by_dir_entry_free(ent);
				return 0;
				}
			strncpy(ent->dir,ss,(unsigned int)len);
			ent->dir[len] = '\0';
			if (!sk_BY_DIR_ENTRY_push(ctx->dirs, ent))
				{
				by_dir_entry_free(ent);
				return 0;
				}
			}
		} while (*p++ != '\0');
	return 1;
	}
