setStatusMessage(const char * pBuf, int )
{
    if(getFrame()->getFrameMode() != XAP_NormalFrame)
    {
	return;
    }

    if (pBuf && *pBuf)
    {
	UT_UTF8String sBuf(pBuf, XAP_App::getApp()->getDefaultEncoding());
	m_sStatusMessage = sBuf;
    }
	else
	m_sStatusMessage.clear();

    ap_sbf_StatusMessage * pf = static_cast<ap_sbf_StatusMessage *>(m_pStatusMessageField);
    if(pf)
	pf->update(m_sStatusMessage);
}
