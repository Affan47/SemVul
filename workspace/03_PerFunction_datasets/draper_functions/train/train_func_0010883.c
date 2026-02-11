referenceNames(
	CMCIClient * mb,
	CMPIObjectPath * cop,
	const char * resultClass,
	const char * role,
	CMPIStatus * rc)
{
   ClientEnc		*cl = (ClientEnc*)mb;
   CMCIConnection	*con = cl->connection;
   UtilStringBuffer	*sb = UtilFactory->newStringBuffer(2048);
   char			*error;
   CMPIEnumeration      *retval;

   START_TIMING(ReferenceNames);
   SET_DEBUG();

   con->ft->genRequest(cl, ReferenceNames, cop, 0);
   addXmlHeader(sb);

   sb->ft->append3Chars(sb, "<IMETHODCALL NAME=\"", ReferenceNames, "\">");

   addXmlNamespace(sb, cop);

   addXmlObjectName(sb, cop, "ObjectName");

   if (resultClass!=NULL)
      sb->ft->append3Chars(sb,
	      "<IPARAMVALUE NAME=\"ResultClass\"><CLASSNAME NAME=\"",
	      resultClass,
              "\"/></IPARAMVALUE>\n");
   if (role)
      sb->ft->append3Chars(sb,
              "<IPARAMVALUE NAME=\"Role\"><VALUE>",
	      role,
              "</VALUE></IPARAMVALUE>\n");

   sb->ft->appendChars(sb,"</IMETHODCALL>\n");
   addXmlFooter(sb);

   error = con->ft->addPayload(con, sb);

   if (error || (error=con->ft->getResponse(con,cop))) {
      CMSetStatusWithChars(rc,CMPI_RC_ERR_FAILED,error);
      free(error);
      CMRelease(sb);
      END_TIMING(_T_FAILED);
      return NULL;
   }

   if (con->mStatus.rc != CMPI_RC_OK) {
      if (rc)
     *rc=cloneStatus(con->mStatus);
      CMRelease(sb);
      END_TIMING(_T_FAILED);
      return NULL;
   }

   CMRelease(sb);

   ResponseHdr rh=scanCimXmlResponse(CMGetCharPtr(con->mResponse),cop);

   if (rh.errCode!=0) {
      CMSetStatusWithChars(rc,rh.errCode,rh.description);
      free(rh.description);
      CMRelease(rh.rvArray);
      END_TIMING(_T_FAILED);
      return NULL;
   }

#if DEBUG
   if (do_debug)
       printf ("\treturn enumeration array type %d expected CMPI_ref %d\n",
	    rh.rvArray->ft->getSimpleType(rh.rvArray, NULL), CMPI_ref);
#endif

   CMSetStatus(rc,CMPI_RC_OK);
   retval = newCMPIEnumeration(rh.rvArray, NULL);
   END_TIMING(_T_GOOD);
   return retval;
}
