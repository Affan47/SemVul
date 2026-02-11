DrawBitmap(wxDC &dc, wxBitmap &bitmap,
                           int x, int y, int logicalFunc)
{
   if (logicalFunc == wxCOPY)
      dc.DrawBitmap(bitmap, x, y);
   else {
      wxMemoryDC memDC;
      memDC.SelectObject(bitmap);
      dc.Blit(x, y, bitmap.GetWidth(), bitmap.GetHeight(),
              &memDC, 0, 0, logicalFunc);
   }
}
