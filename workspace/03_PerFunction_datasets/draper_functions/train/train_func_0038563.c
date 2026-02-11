SizeOutside(const Range *r) const
{
   return((defined&SIZE) && !r->Match(size));
}
