sftk_ForkReset(CK_VOID_PTR pReserved, CK_RV* crv)
{
#ifndef NO_FORK_CHECK
    if (PARENT_FORKED()) {
        parentForkedAfterC_Initialize = PR_TRUE;
        if (nsc_init) {

            *crv = nsc_CommonFinalize(pReserved, PR_FALSE);
            PORT_Assert(CKR_OK == *crv);
            nsc_init = (PRBool) !(*crv == CKR_OK);
        }
        if (nsf_init) {

            *crv = nsc_CommonFinalize(pReserved, PR_TRUE);
            PORT_Assert(CKR_OK == *crv);
            nsf_init = (PRBool) !(*crv == CKR_OK);
        }
        parentForkedAfterC_Initialize = PR_FALSE;
        return PR_TRUE;
    }
#endif
    return PR_FALSE;
}
