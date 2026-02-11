dump_externalAclHelper(StoreEntry * sentry, const char *name, const external_acl * list)
{
    const external_acl *node;
    const external_acl_format *format;
    const wordlist *word;
    for (node = list; node; node = node->next) {
	storeAppendPrintf(sentry, "%s %s", name, node->name);
	if (node->ttl != DEFAULT_EXTERNAL_ACL_TTL)
	    storeAppendPrintf(sentry, " ttl=%d", node->ttl);
	if (node->negative_ttl != node->ttl)
	    storeAppendPrintf(sentry, " negative_ttl=%d", node->negative_ttl);
	if (node->grace)
	    storeAppendPrintf(sentry, " grace=%d", node->grace);
	if (node->children != DEFAULT_EXTERNAL_ACL_CHILDREN)
	    storeAppendPrintf(sentry, " children=%d", node->children);
	if (node->concurrency)
	    storeAppendPrintf(sentry, " concurrency=%d", node->concurrency);
	if (node->cache_size)
	    storeAppendPrintf(sentry, " cache=%d", node->cache_size);
	for (format = node->format; format; format = format->next) {
	    switch (format->type) {
	    case EXT_ACL_HEADER:
	    case EXT_ACL_HEADER_ID:
		storeAppendPrintf(sentry, " %%{%s}", format->header);
		break;
	    case EXT_ACL_HEADER_MEMBER:
	    case EXT_ACL_HEADER_ID_MEMBER:
		storeAppendPrintf(sentry, " %%{%s:%s}", format->header, format->member);
		break;
#define DUMP_EXT_ACL_TYPE(a) \
	    case EXT_ACL_##a: \
		storeAppendPrintf(sentry, " %%%s", #a); \
		break
		DUMP_EXT_ACL_TYPE(LOGIN);
#if USE_IDENT
		DUMP_EXT_ACL_TYPE(IDENT);
#endif
		DUMP_EXT_ACL_TYPE(SRC);
		DUMP_EXT_ACL_TYPE(SRCPORT);
		DUMP_EXT_ACL_TYPE(MYADDR);
		DUMP_EXT_ACL_TYPE(MYPORT);
		DUMP_EXT_ACL_TYPE(URI);
		DUMP_EXT_ACL_TYPE(DST);
		DUMP_EXT_ACL_TYPE(PROTO);
		DUMP_EXT_ACL_TYPE(PORT);
		DUMP_EXT_ACL_TYPE(PATH);
		DUMP_EXT_ACL_TYPE(METHOD);
		DUMP_EXT_ACL_TYPE(EXT_USER);
#if USE_SSL
	    case EXT_ACL_USER_CERT_RAW:
		storeAppendPrintf(sentry, " %%USER_CERT");
		break;
	    case EXT_ACL_USER_CERTCHAIN_RAW:
		storeAppendPrintf(sentry, " %%USER_CERTCHAIN");
		break;
	    case EXT_ACL_USER_CERT:
		storeAppendPrintf(sentry, " %%USER_CERT_%s", format->header);
		break;
	    case EXT_ACL_CA_CERT:
		storeAppendPrintf(sentry, " %%CA_CERT_%s", format->header);
		break;
#endif
		DUMP_EXT_ACL_TYPE(ACL);
		DUMP_EXT_ACL_TYPE(DATA);
	    case EXT_ACL_UNKNOWN:
	    case EXT_ACL_END:
		fatal("unknown external_acl format error");
		break;
	    }
	}
	for (word = node->cmdline; word; word = word->next)
	    storeAppendPrintf(sentry, " %s", word->key);
	storeAppendPrintf(sentry, "\n");
    }
}
