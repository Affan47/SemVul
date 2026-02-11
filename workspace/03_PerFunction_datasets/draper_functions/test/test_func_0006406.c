Argusgen_prototype(unsigned int proto)
{
   struct block *b0, *b1;

   switch (proto) {
      case IPPROTO_RTP:
         b0 = Argusgen_cmp(48, BPF_B, (u_int) IPPROTO_UDP);
         b1 = Argusgen_cmp(49, BPF_B, (u_int) ARGUS_RTP_FLOWTAG);
         Argusgen_and(b0, b1);
         break;

      default:
         b1 = Argusgen_cmp(48, BPF_B, (u_int) proto);
         break;
   }

   return b1;
}
