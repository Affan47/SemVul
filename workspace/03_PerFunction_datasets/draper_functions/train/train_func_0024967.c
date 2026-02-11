ungrabKeyboard(Window window_,Time time)
{
  MSUnsignedLongVector *pGrabList=(MSUnsignedLongVector *)_keyboardGrabList;
  if (pGrabList->length()>0)
   {
     int index=pGrabList->length()-1;
     MSBoolean found=MSFalse;

     while (found==MSFalse&&index>=0)
      {
	KeyboardGrabber *pGrabWidget=(KeyboardGrabber *)((*pGrabList)(index));


	if (pGrabWidget->_grabWindow==window_)
	 {
	   found=MSTrue;
	   if (index-1>=0)
	    {
	      KeyboardGrabber *pGrabber=(KeyboardGrabber *)((*pGrabList)(index-1));
	      int ret=XGrabKeyboard(_dpy,pGrabber->_grabWindow,pGrabber->_ownerEvents,
				    pGrabber->_pointerMode,pGrabber->_keyboardMode,pGrabber->_time);
	      if (ret!=GrabSuccess)
	       {
		 fprintf(stderr, "Warning : Unable to revert keyboard grab to Window %ld\n",pGrabber->_grabWindow);
		 _keyboardGrabber=0;
	       }
	      else _keyboardGrabber=pGrabber->_grabWindow;
	    }
	   else
	    {
	      XUngrabKeyboard(_dpy,time);
	      _keyboardGrabber=0;
	    }

           for(int j=index;j<pGrabList->length();j++)
            {
	      KeyboardGrabber *pGrabber=(KeyboardGrabber *)((*pGrabList)(j));
	      delete pGrabber;
            }
           pGrabList->removeAt(index, pGrabList->length()-index);
	 }
        index--;
      }


     if (found==MSFalse)
      {
	KeyboardGrabber *pGrabber=(KeyboardGrabber *)
          ((const MSWidgetVector *)pGrabList)->lastElement();
	int ret=XGrabKeyboard(_dpy,pGrabber->_grabWindow,pGrabber->_ownerEvents,
			      pGrabber->_pointerMode,pGrabber->_keyboardMode,pGrabber->_time);
	if (ret!=GrabSuccess)
	 {
	   fprintf(stderr, "Warning : Unable to revert keyboard grab to Window %ld\n",pGrabber->_grabWindow);
	   _keyboardGrabber=0;
	 }
	else _keyboardGrabber=pGrabber->_grabWindow;
      }
   }
  else
   {
     XUngrabKeyboard(_dpy,time);
     _keyboardGrabber=0;
   }
}
