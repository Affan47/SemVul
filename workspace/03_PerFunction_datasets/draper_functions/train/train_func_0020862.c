setFGColor(int)
{
  MSBoolean 	status=MSFalse;

  if (fgColor()!=gcValues().foreground)
   {
     updateForeground();
     if (fgRGB().red==fgRGB().green&&fgRGB().green==fgRGB().blue)
      {
	pout<< (double)(fgRGB().red)/65536.0;
	pout<< " ";
	pout<< "sg";
      }
     else
      {
	pout<< (double)(fgRGB().red>>8);
	pout<< " ";
	pout<< (double)(fgRGB().green>>8);
	pout<< " ";
	pout<< (double)(fgRGB().blue>>8);
	pout<< " ";
	pout<< "tc";
      }
     pout<< " ";
     status=MSTrue;
   }
  return status;
}
