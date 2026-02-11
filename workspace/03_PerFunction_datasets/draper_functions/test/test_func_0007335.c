udpport_string(u_short port)
{
   struct hnamemem *tp;
   unsigned int i = port;

        if (port) {
      for (tp = &uporttable[i & (HASHNAMESIZE-1)]; tp->nxt; tp = tp->nxt)
         if (tp->addr == i)
            return (tp->name);

      tp->name = (char *)malloc(sizeof("00000"));
      tp->addr = i;
      tp->nxt = (struct hnamemem *)calloc(1, sizeof(*tp));

      (void)sprintf(tp->name, "%d", i);

      return (tp->name);
   } else
   return ("*");
}
