NSS_CMSDigestContext_Cancel(NSSCMSDigestContext *cmsdigcx)
{
    int i;
    digestPair *pair = cmsdigcx->digPairs;

    for (i = 0; i < cmsdigcx->digcnt; i++, pair++) {
	if (pair->digcx) {
	    (*pair->digobj->destroy)(pair->digcx, PR_TRUE);
#ifdef CMS_FIND_LEAK_MULTIPLE
	    --global_num_digests;
#endif
    	}
    }
#ifdef CMS_FIND_LEAK_MULTIPLE
    PORT_Assert(global_num_digests == 0 || !stop_on_err);
#endif
    PORT_FreeArena(cmsdigcx->pool, PR_FALSE);
}
