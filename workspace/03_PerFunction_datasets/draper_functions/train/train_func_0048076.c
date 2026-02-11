activate(void)
{
  if (menu()!=0)
   {
     menu()->releaseGrab();
     state(MSTrue);
     if (showState()==ShowBoth) drawPixmap();
     else drawSymbol();
     menu()->enforceRadioBehavior();
     if (activateCallback(MSWidgetCallback::activate)==MSFalse) menu()->activate();
     else menu()->done();
   }
}
