hasExtent() const
{
  return !(min[0] == FLT_MAX || min[1] == FLT_MAX || min[2] == FLT_MAX ||
	   max[0] == -FLT_MAX || max[1] == -FLT_MAX || max[2] == -FLT_MAX);
}
