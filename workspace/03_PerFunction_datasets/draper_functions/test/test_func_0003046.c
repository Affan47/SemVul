notify(int)
{
  switch(changeType())
   {
   case Inc:         increment(); break;
   case Dec:         decrement(); break;
   case PageDown:    pageDown();  break;
   case PageUp:      pageUp();    break;
   case Drag:        drag();      break;
   case ValueChange: change();    break;
   case Home:        home();      break;
   case End:         end();       break;
   case NoChange:                 break;
   }
}
