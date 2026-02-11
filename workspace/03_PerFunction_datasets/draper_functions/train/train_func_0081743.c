zx_DEC_ELEM_mm7_ReplaceReq(struct zx_ctx* c, struct zx_mm7_ReplaceReq_s* x)
{
  struct zx_elem_s* el = x->gg.kids;
  switch (el->g.tok) {
  case zx_mm7_MM7Version_ELEM:
    if (!x->MM7Version)
      x->MM7Version = el;
    return 1;
  case zx_mm7_SenderIdentification_ELEM:
    if (!x->SenderIdentification)
      x->SenderIdentification = (struct zx_mm7_SenderIdentification_s*)el;
    return 1;
  case zx_mm7_Extension_ELEM:
    if (!x->Extension)
      x->Extension = (struct zx_mm7_Extension_s*)el;
    return 1;
  case zx_mm7_MessageID_ELEM:
    if (!x->MessageID)
      x->MessageID = el;
    return 1;
  case zx_mm7_ServiceCode_ELEM:
    if (!x->ServiceCode)
      x->ServiceCode = (struct zx_mm7_ServiceCode_s*)el;
    return 1;
  case zx_mm7_TimeStamp_ELEM:
    if (!x->TimeStamp)
      x->TimeStamp = el;
    return 1;
  case zx_mm7_ReadReply_ELEM:
    if (!x->ReadReply)
      x->ReadReply = el;
    return 1;
  case zx_mm7_EarliestDeliveryTime_ELEM:
    if (!x->EarliestDeliveryTime)
      x->EarliestDeliveryTime = el;
    return 1;
  case zx_mm7_DistributionIndicator_ELEM:
    if (!x->DistributionIndicator)
      x->DistributionIndicator = el;
    return 1;
  case zx_mm7_ContentClass_ELEM:
    if (!x->ContentClass)
      x->ContentClass = el;
    return 1;
  case zx_mm7_DRMContent_ELEM:
    if (!x->DRMContent)
      x->DRMContent = el;
    return 1;
  case zx_mm7_ApplicID_ELEM:
    if (!x->ApplicID)
      x->ApplicID = el;
    return 1;
  case zx_mm7_ReplyApplicID_ELEM:
    if (!x->ReplyApplicID)
      x->ReplyApplicID = el;
    return 1;
  case zx_mm7_AuxApplicInfo_ELEM:
    if (!x->AuxApplicInfo)
      x->AuxApplicInfo = el;
    return 1;
  case zx_mm7_Content_ELEM:
    if (!x->Content)
      x->Content = (struct zx_mm7_Content_s*)el;
    return 1;
  case zx_mm7_AdditionalInformation_ELEM:
    if (!x->AdditionalInformation)
      x->AdditionalInformation = (struct zx_mm7_AdditionalInformation_s*)el;
    return 1;
  case zx_mm7_MessageExtraData_ELEM:
    if (!x->MessageExtraData)
      x->MessageExtraData = (struct zx_mm7_MessageExtraData_s*)el;
    return 1;

  default: return 0;
  }
}
