traverseFocus(MSWidget *newFocusWidget_)
{
  static MSSymbol takeFocusSymbol("takefocus");
  if (AplusShell::allowNestedTraversal())
   {
     MSBoolean lf=MSTrue;
     if (focusWidget()!=0&&focusWidget()!=newFocusWidget_) lf=loseFocusNotify(focusWidget());
     if (lf==MSTrue)
      {
	focusWidget(newFocusWidget_);
	takeFocusNotify(focusWidget());
	activateCallback(focusWidget(),takeFocusSymbol);
	return MSTrue;
      }
     return MSFalse;
   }
  else return MSPopup::traverseFocus(newFocusWidget_);
}
