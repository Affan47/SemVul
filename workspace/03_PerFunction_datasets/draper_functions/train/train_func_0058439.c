clientStoreURLRewriteStart(clientHttpRequest * http)
{
    debug(85, 5) ("clientStoreURLRewriteStart: '%s'\n", http->uri);
    if (Config.Program.store_rewrite.command == NULL) {
	clientStoreURLRewriteDone(http, NULL);
	return;
    }
    if (Config.accessList.storeurl_rewrite) {
	http->acl_checklist = clientAclChecklistCreate(Config.accessList.storeurl_rewrite, http);
	aclNBCheck(http->acl_checklist, clientStoreURLRewriteAccessCheckDone, http);
    } else {
	storeurlStart(http, clientStoreURLRewriteDone, http);
    }
}
