EB_Xml_BuildNodeHash(xmlNodePtr node,
			 const char *uri,
                         GWEN_MDIGEST *md,
			 GWEN_BUFFER *hbuf) {
  GWEN_BUFFER *dbuf;
  int rv;

  dbuf=GWEN_Buffer_new(0, 1024, 0, 1);
  rv=EB_Xml_BuildHashData(node, BAD_CAST uri, dbuf);
  if (rv) {
    DBG_INFO(AQEBICS_LOGDOMAIN, "here (%d)", rv);
    GWEN_Buffer_free(dbuf);
    return rv;
  }


  rv=GWEN_MDigest_Begin(md);
  if (rv<0) {
    DBG_ERROR(AQEBICS_LOGDOMAIN, "here (%d)", rv);
    GWEN_Buffer_free(dbuf);
    return EB_RC_INTERNAL_ERROR;
  }


  rv=GWEN_MDigest_Update(md,
			 (const uint8_t*) GWEN_Buffer_GetStart(dbuf),
			 GWEN_Buffer_GetUsedBytes(dbuf));
  if (rv<0) {
    DBG_ERROR(AQEBICS_LOGDOMAIN, "here (%d)", rv);
    GWEN_Buffer_free(dbuf);
    return EB_RC_INTERNAL_ERROR;
  }


  rv=GWEN_MDigest_End(md);
  if (rv<0) {
    DBG_ERROR(AQEBICS_LOGDOMAIN, "here (%d)", rv);
    GWEN_Buffer_free(dbuf);
    return EB_RC_INTERNAL_ERROR;
  }

  GWEN_Buffer_AppendBytes(hbuf,
			  (const char*)GWEN_MDigest_GetDigestPtr(md),
			  GWEN_MDigest_GetDigestSize(md));

  GWEN_Buffer_free(dbuf);

  return 0;
}
