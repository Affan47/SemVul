ListXY (int cnt, int isY)
{
  int max = mapMode;
  int w = CompactOptions ? 70 : 105, h = CompactOptions ? 45 : 80;
  while ((draw->allocation.width/w) * (draw->allocation.height/h - 1) > max) {
    w++;
    h++;
  }
  return isY ? cnt / (draw->allocation.width / w) * h + h / 2 - listYOffset :
    (cnt % (draw->allocation.width / w)) * w + w / 2;
}
