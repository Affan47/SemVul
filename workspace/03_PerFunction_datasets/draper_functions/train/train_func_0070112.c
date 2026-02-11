draw_longitude(double lngtd, double lat_min, double lat_max,
		      bool front, const Sphere& S, const frame& coords)
  {
    P center(S.center());
    double radius(S.radius());

    path temp(center,
	      radius*(Cos(lngtd)*coords.sea()+Sin(lngtd)*coords.sky() ),
	      radius*coords.eye(), lat_min, lat_max);

    temp.clip_to(S, cam().viewpt(), front);
    temp.draw();
  }
