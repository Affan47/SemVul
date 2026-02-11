ArgusCalloc (int nitems, int size)
{
   unsigned int *retn = NULL;
   int bytes = nitems * size;

   if (size) {
      ArgusCallocTotal++;
      retn = (unsigned int *) calloc (1, bytes + 4);

      *retn = 0x45672381;
      retn++;
   }

#ifdef ARGUSDEBUG
   ArgusDebug (4, "ArgusCalloc (%d, %d) returning 0x%x\n", nitems, size, retn);
#endif
   return ((void *) retn);
}
