removeSash(int row_,int col_)
{
  sashAction(MSTrue);
  MSSash *pSash;
  for (unsigned i=0;i<sashList().length();i++)
   {
     pSash=(MSSash *)_sashList(i);
     if (pSash->row()==row_&&pSash->column()==col_)
      {
        sashList().removeAt(i);
	delete pSash;
	break;
      }
   }
  sashAction(MSFalse);
}
