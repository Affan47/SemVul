setFocus(MSWidget *pWidget_)
{
  if (pWidget_->_owner!=0&&pWidget_->sensitive()==MSTrue&&pWidget_->acceptFocus()==MSTrue)
   {
     MSWidget *pTopWidget=pWidget_->top();
     MSWidget::_focusWindow=pTopWidget;
     return pTopWidget->traverseFocus(pWidget_);
   }
  return MSFalse;
}
