contains(const Vector &rhs) const
{

  return (iMin.x <= rhs.x && rhs.x <= iMax.x &&
	  iMin.y <= rhs.y && rhs.y <= iMax.y);
}
