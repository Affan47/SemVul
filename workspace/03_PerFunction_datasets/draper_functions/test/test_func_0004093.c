DispatchMethodReply()

{ char label[CF_BUFSIZE];
  char ipaddress[CF_SMALLBUF],clientip[CF_SMALLBUF];

Verbose("DispatchMethodReply()\n\n");

if (strcmp(METHODREPLYTO,"localhost") == 0 || strcmp(METHODREPLYTO,"::1") == 0 || strcmp(METHODREPLYTO,"127.0.0.1") == 0)
   {
   snprintf(label,CF_BUFSIZE-1,"%s/rpc_in/localhost+localhost+%s:Reply+%s",VLOCKDIR,METHODNAME,METHODMD5);
   EncapsulateReply(label);
   }
else
   {
   strncpy(clientip,Hostname2IPString(METHODREPLYTO),63);
   strncpy(ipaddress,Hostname2IPString(VFQNAME),63);

   Verbose("\nDispatch method %s:%s to %s/rpc_out\n",METHODREPLYTO,METHODNAME,VLOCKDIR);

   snprintf(label,CF_BUFSIZE-1,"%s/rpc_out/%s+%s+%s:Reply+%s",VLOCKDIR,clientip,ipaddress,METHODNAME,METHODMD5);
   EncapsulateReply(label);
   }
}
