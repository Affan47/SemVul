headingAreaSelection(const XEvent *pEvent_)
{
  int col=(pEvent_->xbutton.x<(fixedColumnPixelWidth()+labelWidth()))?
          xToColumn(pEvent_->xbutton.x-labelWidth()):
          xToColumn(pEvent_->xbutton.x-labelWidth())+firstColumn();
  if (inColRange(col)==MSTrue)
   {
     if (pEvent_->xbutton.state&Mod1Mask)
      {
	if(columnDragDrop()==MSTrue) dragColumn(pEvent_,col);
      }
     else
      {
	if (selectedColumn()!=col)
	 {
	   int row;
	   if (selectedRow()<0&&numRows()>0) row=0;
	   else row=selectedRow();
	   if (row>=0)
	    {
	      if (hasCallback(MSWidgetCallback::columnselection)==MSTrue||
                  hasCallback(MSWidgetCallback::columnmenubutton)==MSTrue)
               {
                 setSelection(row,col);
               }
              else selectedRowColumn(row,col);
	    }
	 }
	if (selectedColumn()>=0&&selectedRow()>=0)
         {
           if (pEvent_->xbutton.button==Button3)
            {
              columnMenuButtonSelection();
            }
           else
            {
              columnSelection();
            }
         }

      }
   }
}
