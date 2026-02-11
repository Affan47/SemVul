Argusgen_ncode(char *s, u_int v, struct qual q)
{
   u_int mask;
   int proto = q.proto;
   int dir = q.dir;
   int vlen;

   if (s == NULL)
      vlen = 32;
   else
      vlen = __argus_atoin(s, &v);

   switch (q.addr) {

   case Q_DEFAULT:
   case Q_HOST:
   case Q_NET:
      if (proto == Q_LINK) {
         ArgusLog(LOG_ERR, "illegal link layer address");

      } else {


         mask = 0xffffffff;
         if ((s == NULL) && (q.addr == Q_NET)) {

            while (v && (v & 0xff000000) == 0) {
               v <<= 8;
               mask <<= 8;
            }
         } else {

            v <<= 32 - vlen;
            mask <<= 32 - vlen;
         }

         return Argusgen_host(v, mask, proto, dir);
      }

   case Q_SRCID:
      mask = 0xffffffff;
      return Argusgen_srcid(v, mask);

   case Q_PORT:
      if (proto == Q_UDP)
         proto = IPPROTO_UDP;
      else if (proto == Q_RTP)
         proto = IPPROTO_RTP;
      else if (proto == Q_RTCP)
         proto = IPPROTO_RTCP;
      else if (proto == Q_TCP)
         proto = IPPROTO_TCP;
      else if (proto == Q_DEFAULT)
         proto = PROTO_UNDEF;
      else
         ArgusLog(LOG_ERR, "illegal qualifier of 'port'");

      return Argusgen_port((int)v, proto, dir);

   case Q_GATEWAY:
      ArgusLog(LOG_ERR, "'gateway' requires a name");


   case Q_PROTO:
      return Argusgen_proto((int)v, proto, dir);

   case Q_TTL:
      return Argusgen_ttl((int)v, dir);

   case Q_TOS:
      return Argusgen_tos((int)v, dir);

   case Q_VLANID:
      return Argusgen_vid((int)v, dir);

   case Q_MPLSID:
      return Argusgen_mid((int)v, dir);

   case Q_UNDEF:
      syntax();


   default:
      abort();

   }

}
