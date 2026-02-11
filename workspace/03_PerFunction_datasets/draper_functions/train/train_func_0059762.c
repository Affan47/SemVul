straight(const double precision) const
{
  if (iAlpha == 0.0 && iBeta == IpeTwoPi)
    return false;

  return Angle(iBeta).normalize(iAlpha) - iAlpha < precision;
}
