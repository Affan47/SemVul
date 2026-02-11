encodeGetMsgPtr (OOCTXT* pctxt, int* pLength)
{
   if (pLength) *pLength = getPERMsgLen (pctxt);
   return pctxt->buffer.data;
}
