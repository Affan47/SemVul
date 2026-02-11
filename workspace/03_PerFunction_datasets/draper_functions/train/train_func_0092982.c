ArgusLookUpNetFlow(struct ARGUS_INPUT *input, int type)
{
   ArgusNetFlowHandler retn = NULL;
   struct ArgusNetFlowParsers *p = ArgusNetFlowParsers;

   do {
      if (type == p->type) {
         retn = p->proc;
         input->ArgusReadSize = p->size;
         break;
      }
      p++;
   } while (p->type != -1);

#ifdef ARGUSDEBUG
   ArgusDebug (1, "ArgusLookUpNetFlow (0x%x, %d) returning 0x%x\n", input, type, retn);
#endif

   return (retn);
}
