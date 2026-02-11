NSS_InitContext(const char *configdir, const char *certPrefix,
	const char *keyPrefix, const char *secmodName,
	NSSInitParameters *initParams, PRUint32 flags)
{
    SECStatus rv;
    NSSInitContext *context;

    rv = nss_Init(configdir, certPrefix, keyPrefix, secmodName,
	"", "", "", "", "", &context, initParams,
	((flags & NSS_INIT_READONLY) == NSS_INIT_READONLY),
	((flags & NSS_INIT_NOCERTDB) == NSS_INIT_NOCERTDB),
	((flags & NSS_INIT_NOMODDB) == NSS_INIT_NOMODDB),
	((flags & NSS_INIT_FORCEOPEN) == NSS_INIT_FORCEOPEN), PR_TRUE,
	((flags & NSS_INIT_OPTIMIZESPACE) == NSS_INIT_OPTIMIZESPACE),
        ((flags & NSS_INIT_PK11THREADSAFE) == NSS_INIT_PK11THREADSAFE),
        ((flags & NSS_INIT_PK11RELOAD) == NSS_INIT_PK11RELOAD),
        ((flags & NSS_INIT_NOPK11FINALIZE) == NSS_INIT_NOPK11FINALIZE));
    return (rv == SECSuccess) ? context : NULL;
}
