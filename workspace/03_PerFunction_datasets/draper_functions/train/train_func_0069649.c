sendAcctChangePasswordRequest(const plString& acctName,
                const plString& password)
{
    const pnNetMsg* desc = GET_Cli2Auth(kCli2Auth_AcctChangePasswordRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fString = plwcsdup(acctName.wstr());
    pnSha1Hash hash = NCHashPassword(acctName, password);
    memcpy(msg[2].fData, &hash, sizeof(hash));
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}
