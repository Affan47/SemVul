add(MSWidget *pWidget_)
{
  if (_widgetList.indexOf((unsigned long)pWidget_)==_widgetList.length())
   {
     _widgetList.append((unsigned long)pWidget_);
   }
}
