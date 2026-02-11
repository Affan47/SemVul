create_sinestar(double cx, double cy, double size, int nArms, double armLenRat)
{
	geos::geom::util::SineStarFactory fact(global_factory);
	fact.setCentre(Coordinate(cx, cy));
	fact.setSize(size);
	fact.setNumPoints(nArms*5);
  fact.setArmLengthRatio(armLenRat);
	fact.setNumArms(nArms);
	return fact.createSineStar();
}
