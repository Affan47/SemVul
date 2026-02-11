DrawFocus(wxDC & dc, wxRect & rect)
{


   wxCoord x1 = rect.GetLeft(),
         y1 = rect.GetTop(),
         x2 = rect.GetRight(),
         y2 = rect.GetBottom();

   dc.SetPen(wxPen(wxT("MEDIUM GREY"), 0, wxSOLID));


   dc.SetLogicalFunction(wxAND_REVERSE);

   wxCoord z;
   for ( z = x1 + 1; z < x2; z += 2 )
      dc.DrawPoint(z, y1);

   wxCoord shift = z == x2 ? 0 : 1;
   for ( z = y1 + shift; z < y2; z += 2 )
      dc.DrawPoint(x2, z);

   shift = z == y2 ? 0 : 1;
   for ( z = x2 - shift; z > x1; z -= 2 )
      dc.DrawPoint(z, y2);

   shift = z == x1 ? 0 : 1;
   for ( z = y2 - shift; z > y1; z -= 2 )
      dc.DrawPoint(x1, z);

   dc.SetLogicalFunction(wxCOPY);
}
