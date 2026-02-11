Draw( void ) {
  Window::Draw();

  if ( head ) {
    Font *tf = (flags & WIN_FONT_BIG) ? LargeFont() : SmallFont();
    short xoff = (w - tf->TextWidth(head)) / 2;
    tf->Write( head, this, xoff + 3, 8, GetBGPen() );
    tf->Write( head, this, xoff, 5, GetFGPen() );
  }
}
