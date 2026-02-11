ShowThinking (leaf *p, uint8_t ply)
{
   if (flags & XBOARD)
      return;
   if (!(flags & POST))
      return;
   if (NodeCnt < 500000 && (flags & SOLVE)) {
      return;
   }
   SANMove (p->move, ply);
   printf ("\r%2d.         %2d/%2d%10s    ", Idepth,
      (int) (p-TreePtr[ply]+1), (int) (TreePtr[ply+1]-TreePtr[ply]), SANmv);
   fflush (stdout);
}
