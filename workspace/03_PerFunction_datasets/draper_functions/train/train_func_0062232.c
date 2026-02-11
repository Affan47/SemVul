operator<(const Ids3& p1, const Ids3& p2) {
  if (p1.id1 < p2.id1 ||
     p1.id1 == p2.id1 && p1.id2 < p2.id2 ||
     p1.id1 == p2.id1 && p1.id2 == p2.id2 && p1.id3 < p2.id3)
    return true;
  else
    return false;
}
