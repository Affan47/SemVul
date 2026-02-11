CompareMD5Net(char *file1,char *file2,struct Image *ip)

{ static unsigned char d[CF_MD5_LEN];
  char *sp,sendbuffer[CF_BUFSIZE],recvbuffer[CF_BUFSIZE],in[CF_BUFSIZE],out[CF_BUFSIZE];
  int i,tosend,cipherlen;


ChecksumFile(file2,d,'m');
Debug("Send digest of %s to server, %s\n",file2,ChecksumPrint('m',d));

memset(recvbuffer,0,CF_BUFSIZE);

if (ip->encrypt == 'y')
   {
   snprintf(in,CF_BUFSIZE,"MD5 %s",file1);

   sp = in + strlen(in) + CF_SMALL_OFFSET;

   for (i = 0; i < CF_MD5_LEN; i++)
      {
      *sp++ = d[i];
      }

   cipherlen = EncryptString(in,out,CONN->session_key,strlen(in)+CF_SMALL_OFFSET+CF_MD5_LEN);
   snprintf(sendbuffer,CF_BUFSIZE,"SMD5 %d",cipherlen);
   memcpy(sendbuffer+CF_PROTO_OFFSET,out,cipherlen);
   tosend = cipherlen + CF_PROTO_OFFSET;
   }
else
   {
   snprintf(sendbuffer,CF_BUFSIZE,"MD5 %s",file1);
   sp = sendbuffer + strlen(sendbuffer) + CF_SMALL_OFFSET;

   for (i = 0; i < CF_MD5_LEN; i++)
      {
      *sp++ = d[i];
      }

   tosend = strlen(sendbuffer)+CF_SMALL_OFFSET+CF_MD5_LEN;
   }

if (SendTransaction(CONN->sd,sendbuffer,tosend,CF_DONE) == -1)
   {
   CfLog(cferror,"","send");
   return false;
   }

if (ReceiveTransaction(CONN->sd,recvbuffer,NULL) == -1)
   {
   Verbose("No answer from host, assuming checksum ok to avoid remote copy for now...\n");
   return false;
   }

if (strcmp(CFD_TRUE,recvbuffer) == 0)
   {
   Debug("MD5 mismatch: (reply - %s)\n",recvbuffer);
   return true;
   }
else
   {
   Debug("MD5 matched ok: (reply - %s)\n",recvbuffer);
   return false;
   }


}
