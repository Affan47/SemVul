setDefaultFocus(void)
{
  MSWidget *pWidget=0;
  for (unsigned i=0;i<_traversalList.length();i++)
   {
     pWidget=_traversalList(i);
     if (pWidget!=0&&pWidget->sensitive()==MSTrue&&pWidget->acceptFocus()==MSTrue) break;
     else pWidget=0;
   }
  if (pWidget!=0&&pWidget!=this)
   {
     MSBoolean lf=MSTrue;
     if (_focusWidget!=0) lf=loseFocusNotify(_focusWidget);
     if (lf==MSTrue)
      {
        focusWidget(pWidget);
        takeFocusNotify(_focusWidget);
      }
   }
}
