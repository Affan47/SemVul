SendPropfind(const xstring& efile,int depth)
{
   SendMethod("PROPFIND",efile);
   Send("Depth: %d\r\n",depth);
   if(allprop_len>0)
   {
      Send("Content-Type: text/xml\r\n");
      Send("Content-Length: %d\r\n",allprop_len);
   }
}
