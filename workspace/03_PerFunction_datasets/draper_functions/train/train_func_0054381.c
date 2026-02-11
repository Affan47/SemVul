pkix_PolicyNode_Equals(
        PKIX_PL_Object *firstObject,
        PKIX_PL_Object *secondObject,
        PKIX_Boolean *pResult,
        void *plContext)
{
        PKIX_PolicyNode *firstPN = NULL;
        PKIX_PolicyNode *secondPN = NULL;
        PKIX_UInt32 secondType;
        PKIX_Boolean compResult = PKIX_FALSE;

        PKIX_ENTER(CERTPOLICYNODE, "pkix_PolicyNode_Equals");
        PKIX_NULLCHECK_THREE(firstObject, secondObject, pResult);


        PKIX_CHECK(pkix_CheckType
                (firstObject, PKIX_CERTPOLICYNODE_TYPE, plContext),
                PKIX_FIRSTOBJECTNOTPOLICYNODE);


        if (firstObject == secondObject){
                compResult = PKIX_TRUE;
                goto cleanup;
        }


        PKIX_CHECK(PKIX_PL_Object_GetType
                    (secondObject, &secondType, plContext),
                    PKIX_COULDNOTGETTYPEOFSECONDARGUMENT);

        if (secondType != PKIX_CERTPOLICYNODE_TYPE) {
                goto cleanup;
        }


        firstPN = (PKIX_PolicyNode *)firstObject;
        secondPN = (PKIX_PolicyNode *)secondObject;


        PKIX_EQUALS
                (firstPN->children,
                secondPN->children,
                &compResult,
                plContext,
                PKIX_OBJECTEQUALSFAILEDONCHILDREN);

        if (compResult == PKIX_FALSE) {
                goto cleanup;
        }

        PKIX_CHECK(pkix_SinglePolicyNode_Equals
                (firstPN, secondPN, &compResult, plContext),
                PKIX_SINGLEPOLICYNODEEQUALSFAILED);

cleanup:

        *pResult = compResult;

        PKIX_RETURN(CERTPOLICYNODE);
}
