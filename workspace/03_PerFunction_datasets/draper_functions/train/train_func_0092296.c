calcSpecular(vec3 &c, Geometry *shape, Ray eyeRay, Ray lightRay, vec3 N, Light light, double intensity){
	vec3 E = eyeRay.getDirection();
	vec3 L = lightRay.getDirection();


	vec3 R = normalize((2 * dot(N,L)*N) - L);
	double d = dot(E,R);
	if(d > 0){
		double spec = pow(d,shape->getCosPower()) * shape->getSpecular();
		c += intensity * spec * light.getColor();
	}
}
