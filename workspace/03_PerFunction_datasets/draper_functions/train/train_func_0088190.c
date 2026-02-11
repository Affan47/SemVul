parse (const char * buffer, UT_uint32 length)
{
  if (!m_bSniffing)
    {
      UT_ASSERT (m_pListener || m_pExpertListener);
      if ((m_pListener == 0) && (m_pExpertListener == 0)) return UT_ERROR;
    }
  UT_ASSERT (buffer);
  if (buffer == 0 || length == 0) return UT_ERROR;

  if (!reset_all ()) return UT_OUTOFMEM;

  UT_Error ret = UT_OK;

  xmlParserCtxtPtr ctxt;

  xmlSAXHandler hdl;
  memset(&hdl, 0, sizeof(hdl));

  hdl.getEntity    = _getEntity;
  hdl.startElement = _startElement;
  hdl.endElement   = _endElement;
  hdl.characters   = _charData;
  hdl.error        = _errorSAXFunc;
  hdl.fatalError   = _fatalErrorSAXFunc;
  hdl.processingInstruction = _processingInstruction;
  hdl.comment      = _comment;
  hdl.cdataBlock   = _cdata;

  ctxt = xmlCreateMemoryParserCtxt (buffer, static_cast<int>(length));
  if (ctxt == NULL)
    {
      UT_DEBUGMSG (("Unable to create libxml2 memory context!\n"));
      return UT_ERROR;
    }
  memcpy(ctxt->sax, &hdl, sizeof(hdl));
  ctxt->userData = static_cast<void *>(this);

  m_bStopped = false;

  xmlParseDocument (ctxt);

  if (!ctxt->wellFormed) ret = UT_IE_IMPORTERROR;

  xmlDocPtr myXmlDoc = ctxt->myDoc;
  xmlFreeParserCtxt (ctxt);
  xmlFreeDoc(myXmlDoc);

  return ret;
}
