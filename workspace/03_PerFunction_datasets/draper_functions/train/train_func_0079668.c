GetToolbarBitmap()
{
   wxSize size = GetClientSize();
   wxBitmap bitmap(size.x, size.y);
   wxClientDC winDC(this);
   wxMemoryDC memDC;
   memDC.SelectObject(bitmap);
   memDC.Blit(0, 0, size.x, size.y,
              &winDC, 0, 0);
   return bitmap;
}
