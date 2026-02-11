WriteChecksum(DB *dbp,char type,char *name,unsigned char digest[EVP_MAX_MD_SIZE+1], unsigned char *attr)

{ DBT *key,*value;

key = NewChecksumKey(type,name);
value = NewChecksumValue(digest,attr);

Debug("DATA = %s\n",ChecksumPrint(type,value->data));

if ((errno = dbp->put(dbp,NULL,key,value,0)) != 0)
   {
   snprintf(OUTPUT,CF_BUFSIZE,"Checksum write failed: %s",db_strerror(errno));
   CfLog(cferror,OUTPUT,"db->put");

   DeleteChecksumKey(key);
   DeleteChecksumValue(value);
   return false;
   }
else
   {
   DeleteChecksumKey(key);
   DeleteChecksumValue(value);
   return true;
   }
}
