headingAreaSelection(const XEvent *pEvent_)
{

  int col=columnFromEvent(pEvent_);
  if (inColRange(col)==MSTrue)
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
