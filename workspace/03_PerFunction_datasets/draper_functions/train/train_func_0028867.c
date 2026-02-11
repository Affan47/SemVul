intersect(const Ray &ray)
{
	double a, b, c, d, t1, t2, t;
	Vector N;
	Point P;


	a = ray.D.x*ray.D.x + ray.D.z*ray.D.z;
	b = 2 * (ray.O.x*ray.D.x - pos.x*ray.D.x + ray.O.z*ray.D.z - pos.z*ray.D.z);
	c = ray.O.x*ray.O.x + pos.x*pos.x + ray.O.z*ray.O.z + pos.z*pos.z -
		2 * (ray.O.x*pos.x + ray.O.z*pos.z) - r*r;
	d = b*b - 4*a*c;

	if (d < 0)
		return intersectTopBottom(ray);
	t1 = (-b - sqrt(d)) / (2*a);
	t2 = (-b + sqrt(d)) / (2*a);
	t = t1 < t2 && t1 > 0 ? t1 : t2;
	if (t < 0)
		return intersectTopBottom(ray);
	P = ray.at(t);
	if (P.y < -.5*h+pos.y  || P.y > .5*h+pos.y)
		return intersectTopBottom(ray);

	N.x = P.x - pos.x;
	N.y = 0;
	N.z = P.z - pos.z;
	N.normalize();

	return Hit(t, N, material);
}
