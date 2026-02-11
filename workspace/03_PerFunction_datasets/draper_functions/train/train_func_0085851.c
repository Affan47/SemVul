EventHook(const char *fmt,...)
{
   va_list args;
   int   Wrote;
   char  Line[1024];
   Event *pEvent;

   va_start(args,fmt);
   Wrote = vsnprintf(Line,sizeof(Line),fmt,args);
   va_end(args);

   EndPointEvent(Line);

   if(EventScript != NULL) {
      pEvent = malloc(sizeof(Event) + strlen(Line) + 1);
      if(pEvent != NULL) {
         pEvent->CmdTail = (char *)(pEvent+1);
         strcpy(pEvent->CmdTail,Line);
         QueueEvent(pEvent);
      }
   }
}
