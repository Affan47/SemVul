Evaluate(double *Quadric, double *Point, bool FullQuadric)
{
	double Evaluation=Point[0]*Point[0]*Quadric[0]
	+Point[1]*Point[1]*Quadric[4]
	+Point[2]*Point[2]*Quadric[7]
	+2.0*Point[0]*Point[1]*Quadric[1]
	+2.0*Point[0]*Point[2]*Quadric[2]
	+2.0*Point[1]*Point[2]*Quadric[5]
	+2.0*Point[0]*Quadric[3]
	+2.0*Point[1]*Quadric[6]
	+2.0*Point[2]*Quadric[8];
	if (FullQuadric)
		Evaluation+=Quadric[9];
	return (Evaluation);
}
