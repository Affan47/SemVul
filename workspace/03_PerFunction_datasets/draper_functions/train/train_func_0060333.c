hasListingMode() const
{
  if ( Auth::self()->group() == Auth::Users )
    return false;
  else
    return true;
}
