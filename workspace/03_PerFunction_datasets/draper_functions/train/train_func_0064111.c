ASC_setIdentRQUserOnly(
    T_ASC_Parameters * params,
    const OFString& userName,
    const OFBool& requestRsp)
{
  if (params == NULL)
    return ASC_NULLKEY;

  if (userName.length() > 65535)
    return EC_IllegalCall;
  UserIdentityNegotiationSubItemRQ* rq = params->DULparams.reqUserIdentNeg;
  if (rq == NULL)
    rq = new UserIdentityNegotiationSubItemRQ();
  else
    rq->clear();
  rq->setIdentityType(ASC_USER_IDENTITY_USER);
  rq->setPrimField(userName.c_str(), userName.length());
  rq->setReqPosResponse(requestRsp);
  params->DULparams.reqUserIdentNeg = rq;
  return EC_Normal;
}
