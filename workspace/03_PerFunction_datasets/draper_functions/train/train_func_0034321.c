floodfill(Components &ca, position s, bool fixup=true)
{


  int bestv=0;
  position b = s;
  for(int m=0;m<4;m++) {
    position p = s.next(m);
    if(M(p)) continue;
    int v = ca.connectedvalue(p) + ca.fillablearea(p) - 2*degree(p) -
      4*potential_articulation(p);
    if(v > bestv) { bestv = v; b = p; }
  }
  if(bestv == 0)
    return 0;
  M(b) = 1; ca.remove(b);
  int a = 1+floodfill(ca, b);
  M(b) = 0; if(fixup) ca.add(b);
  return a;
}
