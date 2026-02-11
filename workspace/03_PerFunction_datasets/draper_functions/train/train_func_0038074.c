ASC_refusePresentationContext(
    T_ASC_Parameters * params,
    T_ASC_PresentationContextID presentationContextID,
    T_ASC_P_ResultReason resultReason)


{
    DUL_PRESENTATIONCONTEXT *proposedContext, *acceptedContext;
    OFCondition cond = EC_Normal;
    LST_HEAD *lst;

    proposedContext = findPresentationContextID(
                             params->DULparams.requestedPresentationContext,
                                                presentationContextID);
    if (proposedContext == NULL) return ASC_BADPRESENTATIONCONTEXTID;


    proposedContext->result = resultReason;

    acceptedContext = findPresentationContextID(
                              params->DULparams.acceptedPresentationContext,
                                                presentationContextID);

    if (acceptedContext != NULL) {

        acceptedContext->result = resultReason;
        strcpy(acceptedContext->abstractSyntax,
               proposedContext->abstractSyntax);


        strcpy(acceptedContext->acceptedTransferSyntax,
                UID_LittleEndianImplicitTransferSyntax);
    } else {


        cond = DUL_MakePresentationCtx(
            &acceptedContext,
            DUL_SC_ROLE_DEFAULT, DUL_SC_ROLE_DEFAULT,
            presentationContextID, resultReason,
            proposedContext->abstractSyntax,
            UID_LittleEndianImplicitTransferSyntax, NULL);
        if (cond.bad()) return cond;

        lst = params->DULparams.acceptedPresentationContext;
        if (lst == NULL) {
            lst = LST_Create();
            if (lst == NULL) return EC_MemoryExhausted;
        }
        cond = LST_Enqueue(&lst, (LST_NODE*)acceptedContext);
        if (cond.bad()) return cond;
        params->DULparams.acceptedPresentationContext = lst;
    }
    return EC_Normal;
}
