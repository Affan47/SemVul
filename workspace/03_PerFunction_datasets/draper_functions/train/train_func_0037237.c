countWrapped(void)
{
  UT_sint32 nWrapped = 0;
  UT_sint32 i = 0;
  for(i=0; i<countCons();i++)
  {
      fp_Container * pCon = static_cast<fp_Container*>(getNthCon(i));
      if(pCon->getContainerType() == FP_CONTAINER_LINE)
      {
	  fp_Line * pLine = static_cast<fp_Line *>(pCon);
	  xxx_UT_DEBUGMSG(("Line %d MaxWidth %d \n",i,pLine->getMaxWidth()));
	  if(pLine->isWrapped())
	  {
	      nWrapped++;
	  }
	  else if(pLine->isSameYAsPrevious())
	  {
	      nWrapped++;
	  }
	  else if((pLine->getMaxWidth() > 0) && (pLine->getMaxWidth() < getWidth()))
	  {
	      nWrapped++;

	  }
      }
  }
  return nWrapped;
}
