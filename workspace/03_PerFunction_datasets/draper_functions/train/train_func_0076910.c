process_sa(unsigned char *cp, size_t len, unsigned type, int quiet,
           int multiline, char *hdr_descr) {
   struct isakmp_sa *sa_hdr = (struct isakmp_sa *) cp;
   struct isakmp_proposal *prop_hdr =
      (struct isakmp_proposal *) (cp + sizeof(struct isakmp_sa));
   char *msg;
   char *msg2;
   char *msg3;
   unsigned char *attr_ptr;
   size_t safelen;

   safelen = (ntohs(sa_hdr->isasa_length)<len)?ntohs(sa_hdr->isasa_length):len;


   if (safelen < sizeof(struct isakmp_sa) + sizeof(struct isakmp_proposal) +
       sizeof(struct isakmp_transform))
      return make_message("IKE Handshake returned (packet too short to decode)");


   if (type == ISAKMP_XCHG_IDPROT) {
      msg = make_message("Main Mode Handshake returned");
   } else if (type == ISAKMP_XCHG_AGGR) {
      msg = make_message("Aggressive Mode Handshake returned");
   } else {
      msg = make_message("UNKNOWN Mode Handshake returned (%u)", type);
   }


   if (!quiet) {
      msg2 = msg;
      msg = make_message("%s%s%s", msg2, multiline?"\n\t":" ", hdr_descr);
      free(msg2);
   }


   if (prop_hdr->isap_notrans != 1) {
      msg2 = msg;
      msg = make_message("%s (%d transforms)", msg2, prop_hdr->isap_notrans);
      free(msg2);
   }


   if (!quiet && prop_hdr->isap_notrans==1) {
      int firstloop=1;

      msg2 = msg;
      msg = make_message("%s%sSA=(", msg2, multiline?"\n\t":" ");
      free(msg2);
      if (prop_hdr->isap_spisize != 0) {
         msg2 = msg;
         msg3 = hexstring(cp + sizeof(struct isakmp_sa) +
                          sizeof(struct isakmp_proposal),
                          prop_hdr->isap_spisize);
         msg = make_message("%sSPI=%s ", msg2, msg3);
         free(msg2);
         free(msg3);
      }
      attr_ptr = (cp + sizeof(struct isakmp_sa) +
                  sizeof(struct isakmp_proposal) + prop_hdr->isap_spisize +
                  sizeof(struct isakmp_transform));
      safelen -= sizeof(struct isakmp_sa) +
                 sizeof(struct isakmp_proposal) + prop_hdr->isap_spisize +
                 sizeof(struct isakmp_transform);

      while (safelen) {
         msg2 = msg;
         msg3 = process_attr(&attr_ptr, &safelen);
         if (firstloop) {
            msg = make_message("%s%s", msg2, msg3);
            firstloop=0;
         } else {
            msg = make_message("%s %s", msg2, msg3);
         }
         free(msg2);
         free(msg3);
      }
      msg2 = msg;
      msg = make_message("%s)", msg2);
      free(msg2);
   }

   return msg;
}
