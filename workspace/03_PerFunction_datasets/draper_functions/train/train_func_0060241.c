pkix_VerifyNode_Destroy(
        PKIX_PL_Object *object,
        void *plContext)
{
        PKIX_VerifyNode *node = NULL;

        PKIX_ENTER(VERIFYNODE, "pkix_VerifyNode_Destroy");

        PKIX_NULLCHECK_ONE(object);

        PKIX_CHECK(pkix_CheckType(object, PKIX_VERIFYNODE_TYPE, plContext),
                PKIX_OBJECTNOTVERIFYNODE);

        node = (PKIX_VerifyNode*)object;

        PKIX_DECREF(node->verifyCert);
        PKIX_DECREF(node->children);
        PKIX_DECREF(node->error);

        node->depth = 0;

cleanup:

        PKIX_RETURN(VERIFYNODE);
}
