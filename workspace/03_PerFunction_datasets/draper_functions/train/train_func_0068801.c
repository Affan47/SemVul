addPoint(const Vector &rhs)
{
  if (isEmpty()) {
    iMin = rhs; iMax = rhs;
  } else {
    if (rhs.x > iMax.x)
      iMax.x = rhs.x;
    else if (rhs.x < iMin.x)
      iMin.x = rhs.x;
    if (rhs.y > iMax.y)
      iMax.y = rhs.y;
    else if (rhs.y < iMin.y)
      iMin.y = rhs.y;
  }
}
