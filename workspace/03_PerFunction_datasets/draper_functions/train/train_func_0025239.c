getPERMsgLen (OOCTXT* pctxt)
{
   return (pctxt->buffer.bitOffset == 8) ?
      pctxt->buffer.byteIndex : pctxt->buffer.byteIndex + 1;
}
