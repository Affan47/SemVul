__ecereNameSpace__ecere__net__GetNameFromAddress(char * inetAddress, char * hostName)
{
struct in_addr in;
HOSTENT * host;

if(!__ecereNameSpace__ecere__net__Network_Initialize())
return 0x0;
in.s_addr = inet_addr(inetAddress);
host = gethostbyaddr((unsigned char *)&in, 4, 2);
if(host)
{
strcpy(hostName, (*host).h_name);
return 0x1;
}
return 0x0;
}
