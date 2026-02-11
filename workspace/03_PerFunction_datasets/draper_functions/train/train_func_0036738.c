Argusextract_fddi_addrs(const struct fddi_header *fp, struct ether_header *ehdr)
{
   char *fsrc = (char *)&ehdr->ether_shost;
   char *fdst = (char *)&ehdr->ether_dhost;
   int i;

   if (fddi_bitswap) {
      for (i = 0; i < 6; ++i)
         fdst[i] = fddi_bit_swap[fp->fddi_dhost[i]];
      for (i = 0; i < 6; ++i)
         fsrc[i] = fddi_bit_swap[fp->fddi_shost[i]];
   }
   else {
      bcopy ((char *) fp->fddi_dhost, fdst, 6);
      bcopy ((char *) fp->fddi_shost, fsrc, 6);
   }
}
