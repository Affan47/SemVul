Argusgen_ecode(eaddr, q)
u_char *eaddr;
struct qual q;
{
   struct ablock *b0 = NULL;

   if ((q.addr == Q_HOST || q.addr == Q_DEFAULT) && q.proto == Q_LINK)
      b0 = Argusgen_ehostop(eaddr, (int)q.dir);

   else
      ArgusLog(LOG_ERR, "ethernet address used in non-ether expression");

   return b0;
}
