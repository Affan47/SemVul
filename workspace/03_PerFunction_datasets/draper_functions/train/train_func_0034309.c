DUL_RejectAssociationRQ(
  DUL_ASSOCIATIONKEY ** callerAssociation,
  DUL_ABORTITEMS * params,
  int activatePDUStorage)
{
    PRIVATE_ASSOCIATIONKEY
        ** association;
    DUL_ABORTITEMS
        localParams;

    association = (PRIVATE_ASSOCIATIONKEY **) callerAssociation;
    OFCondition cond = checkAssociation(association);
    if (cond.bad()) return cond;

    if (activatePDUStorage) DUL_activateAssociatePDUStorage(*association);

    localParams = *params;
    localParams.source = 0x01;
    {
        unsigned char diagtable[] = {0x01, 0x02, 0x03, 0x07};
        int l_index;
        OFBool found = OFFalse;
        for (l_index = 0; l_index < (int) DIM_OF(diagtable) && !found; l_index++)
            found = (localParams.reason == diagtable[l_index]);

        if (!found)
        {
            OFOStringStream stream;
            stream << "DUL Illegal reason for rejecting Association: "
                   << STD_NAMESPACE hex << localParams.reason << OFStringStream_ends;
            OFSTRINGSTREAM_GETOFSTRING(stream, msg)
            return makeDcmnetCondition(DULC_ILLEGALREJECTREASON, OF_error, msg.c_str());
        }
    }
    {
        unsigned char resulttable[] = {0x01, 0x02};
        int l_index;
        OFBool found = OFFalse;
        for (l_index = 0; l_index < (int) DIM_OF(resulttable) && !found; l_index++)
            found = (localParams.result == resulttable[l_index]);

        if (!found)
        {
            OFOStringStream stream;
            stream << "DUL Illegal result for rejecting Association: "
                   << STD_NAMESPACE hex << localParams.result << OFStringStream_ends;
            OFSTRINGSTREAM_GETOFSTRING(stream, msg)
            return makeDcmnetCondition(DULC_ILLEGALREJECTRESULT, OF_error, msg.c_str());
        }
    }
    cond = PRV_StateMachine(NULL, association,
                            A_ASSOCIATE_RESPONSE_REJECT, (*association)->protocolState, &localParams);

    return cond;
}
