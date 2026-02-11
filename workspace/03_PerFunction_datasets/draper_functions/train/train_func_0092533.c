refractionRay(Hit h, float n1, float n2){


	Vec3Df n = h.normal;
	Vec3Df i = dest-origin;
	i.normalize();
	float rindex = n1/n2;
	float cosoi = Vec3Df::dotProduct(i,n);
	float sin2ot = rindex*rindex*(1-(cosoi*cosoi));
	Vec3Df t = i*rindex + (rindex*cosoi - sqrt(1-(sin2ot)))*n;

	return Ray(h.hitPoint, h.hitPoint+t, colour, type, h);
}
