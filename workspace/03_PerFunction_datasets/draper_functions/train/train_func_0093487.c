removeAllCycles(void)
{
   MSColorCycle *cycle;
   for (unsigned i=0;i<cycleList().length();i++)
   {
      cycle=(MSColorCycle *)cycleList()(i);
      delete cycle;
   }
   cycleList().removeAll();
   if (cycleTimer()!=0) cycleTimer()->stop();
}
