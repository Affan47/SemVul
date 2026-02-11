Draw( void ) {
  ButtonWidget::Draw();

  short off = (Clicked() ? 1 : 0);
  Color fcol;

  surface->FillRect( x + w - image[0].Width() - 8 + off, y + 4 + off, 1, h - 8, Color(CF_COLOR_SHADOW) );
  surface->FillRect( x + w - image[0].Width() - 7 + off, y + 4 + off, 1, h - 8, Color(CF_COLOR_HIGHLIGHT) );

  image[0].Draw( surface, x + w - image[0].Width() - 4 + off, y + (h - image[0].Height())/2 + off );

  if ( Disabled() ) {
    fcol = font->GetColor();
    font->SetColor( Color(CF_COLOR_GHOSTED) );
  }


  font->Write( choices[val].c_str(), surface,
               x + (w - image[0].Width() - 10 - font->TextWidth(choices[val].c_str()))/2 + off,
               y + (h - font->Height()) / 2 + off, *this );

  if ( Disabled() ) font->SetColor( fcol );
}
