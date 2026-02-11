isNear(
		const HepRotation & r, double epsilon ) const {
  HepBoost    b1;
  HepRotation r1;
  decompose( b1, r1 );
  double db2 = b1.norm2();
  if ( db2 > epsilon*epsilon ) {
     return false;
  }
  double dr2 = r1.distance2(r);
  return ( (db2 + dr2) <= epsilon*epsilon );
}
