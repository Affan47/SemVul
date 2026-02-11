drawDay(MSDay day_)
{
  unsigned daysInMonth=viewDate().daysInMonth();
  if (day_>0&&day_<daysInMonth)
   {
     GridLocation aGridLocation(gridLocationFor(day_));

     int offset=highlightThickness()+shadowThickness();
     int xx=offset + outerMargin() + _dayRect.width()*aGridLocation.column();
     int yy=offset + _dayRect.height()*(2+aGridLocation.row());
     int textOffset = (_dayRect.height() + textAscent())/2;

     MSString aString(day_);
     int tw=textWidth(aString.string(),aString.length());
     int lx=xx+((_dayRect.width()-tw)/2);
     XDrawString(display(),window(),textGC(),textFontStruct(),
		 lx,yy+textOffset,aString.string(),aString.length());
     if (day_==selectedDay())
      {
	MSRect aRect(xx,yy,_dayRect.width()+2,_dayRect.height()+2);
	drawBevel(aRect,MSRaised,2);
      }
   }
}
