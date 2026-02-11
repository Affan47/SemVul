ArgusPrintCounts (char *buf, struct ArgusRecord *argus)
{
   int src_count = 0, dst_count = 0;

   if (argus->ahdr.type & ARGUS_MAR) {
      src_count = argus->argus_mar.pktsRcvd;
      dst_count = argus->argus_mar.pktsDrop;

   } else {
      src_count = argus->argus_far.src.count;
      dst_count = argus->argus_far.dst.count;
   }

   sprintf (buf, "%-8u %-8u  ", src_count, dst_count);
}
