encode_eprt(const sockaddr_u *a)
{
   int proto;
   if(a->sa.sa_family==AF_INET)
      proto=1;
   else if(a->sa.sa_family==AF_INET6)
      proto=2;
   else
      return 0;
   return xstring::format("|%d|%s|%d|",proto,a->address(),a->port());
}
