getCentroid(Coordinate& cent) const
{
  if (std::abs(areasum2) > 0.0) {
    cent.x = cg3.x / 3 / areasum2;
    cent.y = cg3.y / 3 / areasum2;
  }
  else if (totalLength > 0.0) {

    cent.x = lineCentSum.x / totalLength;
    cent.y = lineCentSum.y / totalLength;
  }
  else if (ptCount > 0){
    cent.x = ptCentSum.x / ptCount;
    cent.y = ptCentSum.y / ptCount;
  }
  else {
    return false;
  }
  return true;
}
