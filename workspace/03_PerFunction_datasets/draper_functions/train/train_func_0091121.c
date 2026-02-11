drawCurrentState(void)
{
   if (MSView::model()!=0)
   {
      MSSymbolVector *pSymbolVector=(MSSymbolVector *)_model;
      symbolicState(*pSymbolVector);
   }
}
