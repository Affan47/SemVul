unfreeze(void)
{
  updateInternalState();
  if (frozen()==MSTrue)
   {
     freezeStatus(MSFalse);
     calculateRowHeight();
     calculateHeadingsHeight();
     adjustNumVisible();
     redrawImmediately();
   }
}
