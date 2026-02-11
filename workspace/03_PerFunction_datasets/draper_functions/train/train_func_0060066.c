intersect(const Ray& ray){

	Vector N = normal.normalized();
	double top = (center - ray.O).dot(N);
	double bottom = ray.D.dot(N);


	if(bottom > -1e-6 && bottom < 1e-6){


		return Hit::NO_HIT();
	}

	double t = top / bottom;

	if(t < 0) return Hit::NO_HIT();

	if(N.dot(-ray.D) < 0) N = -N;

	return Hit(t, N);
}
