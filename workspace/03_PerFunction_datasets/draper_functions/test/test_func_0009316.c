mapTexture(const Point in){
	Image * texture = material->texture;

	if(!texture) return material->color;


	Vector vn = Vector(0, 1, 0);
	Vector ve = Vector(1, 0, 0);
	Vector vp = (in - position).normalized();


	Vector d = (position - in).normalized().rotate(angle, axis);
	double u = 0.5 + atan2(d.z,d.x) / (2.0 * M_PI);
	double v = 0.5 - asin(d.y) / M_PI;

	return texture->colorAt(u, v);
}
