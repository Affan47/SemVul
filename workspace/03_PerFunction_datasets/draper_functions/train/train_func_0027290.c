setLineAttributes(void)
{
  MSBoolean	status=MSFalse;

  if (lineWidth()!=gcValues().line_width)
   {
     lineWidth(gcValues().line_width);
     pout<< ((lineWidth()>2)?lineWidth()-1:lineWidth());
     pout<< " ";
     pout<< "w";
     pout<< " ";
     status=MSTrue;
   }
  if (lineStyle()!=gcValues().line_style||updateDash()==MSTrue)
   {
     dashOffset(gcValues().dash_offset);
     switch (gcValues().line_style)
      {
      case LineOnOffDash:
      case LineDoubleDash:
	if (updateDash()==MSTrue&&activeDash()!=0)
	 {
	   pout<<"[ ";
	   for (int i=0; i<activeDash()->dashCt(); i++) pout<<activeDash()->dash(i)<<" ";
	   pout<<"]";
	   pout<<" ";
	   pout<<dashOffset();
	   pout<<" ";
	   pout<<"d";
	   status=MSTrue;
	 }
	break;

      case LineSolid:
      default:
	pout<< "[] 0 d";
	status=MSTrue;
      }
     pout<< " ";
     lineStyle(gcValues().line_style);
   }
  if (capStyle()!=gcValues().cap_style)
   {
     capStyle(gcValues().cap_style);
     pout<< capStyle()-(capStyle()!=0?1:0);
     pout<< " ";
     pout<< "lc";
     pout<< " ";
     status=MSTrue;
   }
  if (joinStyle()!=gcValues().join_style)
   {
     joinStyle(gcValues().join_style);
     pout<< joinStyle();
     pout<< " ";
     pout<< "lj";
     status=MSTrue;
   }
  return status;
}
