getButton( int i )
{
   while ( i >= buttons.size() ) {
      int w = (Width() - 4 * guiIconSpace) / guiIconColumnNum;
      GuiButton* b = new GuiButton ( this, PG_Rect( guiIconSpace + i%3 * (w + guiIconSpace), 10 + guiIconSpace + i/3 * (guiIconSpace + guiIconSizeY), guiIconSizeX, guiIconSizeY));
      buttons.push_back ( b );
      b->Hide();
   }
   return buttons[i];
}
