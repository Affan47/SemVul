ASC_findAcceptedPresentationContextID(
    T_ASC_Association *assoc,
    const char* abstractSyntax)
{


    DUL_PRESENTATIONCONTEXT *pc;
    LST_HEAD **l;
    OFBool found = OFFalse;

    if (assoc->params->DULparams.acceptedPresentationContext == NULL)
      return 0;

    l = &assoc->params->DULparams.acceptedPresentationContext;
    pc = (DUL_PRESENTATIONCONTEXT*) LST_Head(l);
    (void)LST_Position(l, (LST_NODE*)pc);
    while (pc && !found)
    {
        found = ( (strcmp(pc->abstractSyntax, abstractSyntax) == 0) && (pc->result == ASC_P_ACCEPTANCE) );
        if (!found) pc = (DUL_PRESENTATIONCONTEXT*) LST_Next(l);
    }
    if (found) return pc->presentationContextID;
    return 0;
}
