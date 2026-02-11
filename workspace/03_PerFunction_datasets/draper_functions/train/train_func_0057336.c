Itcl_CanAccess(memberPtr, fromNsPtr)
    ItclMember* memberPtr;
    Tcl_Namespace* fromNsPtr;
{
    ItclClass* fromCdPtr;
    Tcl_HashEntry *entry;


    if (memberPtr->protection == ITCL_PUBLIC) {
        return 1;
    }
    else if (memberPtr->protection == ITCL_PRIVATE) {
        return (memberPtr->classDefn->namesp == fromNsPtr);
    }


    assert (memberPtr->protection == ITCL_PROTECTED);

    if (Itcl_IsClassNamespace(fromNsPtr)) {
        fromCdPtr = (ItclClass*)fromNsPtr->clientData;

        entry = Tcl_FindHashEntry(&fromCdPtr->heritage,
            (char*)memberPtr->classDefn);

        if (entry) {
            return 1;
        }
    }
    return 0;
}
