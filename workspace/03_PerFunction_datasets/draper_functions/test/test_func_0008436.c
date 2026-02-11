Print(std::ostream &os) const
{
  Bitmap::Print(os);
  for( std::vector<Overlay>::const_iterator it = Overlays.begin();
    it != Overlays.end(); ++it)
    {
    it->Print( os );
    }
  for( std::vector<Curve>::const_iterator it = Curves.begin();
    it != Curves.end(); ++it)
    {
    it->Print( os );
    }
}
