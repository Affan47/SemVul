nextRightItem(void)
{


   if (itemCount()>0)
   {
      int item=selectedItem();
      MSMenuItem *mi=menuItem(item);
      MSMenuItem *ni=0;
      if (mi==0||item<0)
	 item=-1;

      for (int i=0; i<itemCount();i++)
      {
	 if (item+1==itemCount()) item=0;
	 else item++;
	 ni=menuItem(item);
	 if (ni==mi || ni->sensitive()==MSTrue)
	    return ni;
      }
   }
   return 0;
}
