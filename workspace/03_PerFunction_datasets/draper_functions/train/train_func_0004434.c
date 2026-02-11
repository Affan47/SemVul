RefuseAccess(struct cfd_connection *conn,char *sendbuffer,int size,char *errmesg)

{ char *hostname, *username, *ipaddr;
  static char *def = "?";

if (strlen(conn->hostname) == 0)
   {
   hostname = def;
   }
else
   {
   hostname = conn->hostname;
   }

if (strlen(conn->username) == 0)
   {
   username = def;
   }
else
   {
   username = conn->username;
   }

if (strlen(conn->ipaddr) == 0)
   {
   ipaddr = def;
   }
else
   {
   ipaddr = conn->ipaddr;
   }

snprintf(sendbuffer,CF_BUFSIZE,"%s",CF_FAILEDSTR);
SendTransaction(conn->sd_reply,sendbuffer,size,CF_DONE);
snprintf(sendbuffer,CF_BUFSIZE,"From (host=%s,user=%s,ip=%s)",hostname,username,ipaddr);
CfLog(cfinform,sendbuffer,"");

if (strlen(errmesg) > 0)
   {
   snprintf(OUTPUT,CF_BUFSIZE,"ID from connecting host: (%s)",errmesg);
   if (LOGCONNS)
      {
      CfLog(cfloginform,OUTPUT,"");
      }
   else
      {
      CfLog(cfverbose,OUTPUT,"");
      }
   }
}
