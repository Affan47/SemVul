GCM_DestroyContext(GCMContext *gcm, PRBool freeit)
{


    CTR_DestroyContext(&gcm->ctr_context, PR_FALSE);
    gcmHash_DestroyContext(&gcm->ghash_context, PR_FALSE);
    if (freeit) {
	PORT_Free(gcm);
    }
}
