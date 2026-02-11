getAPoint()
    {
      Vec3 res;

      do{
	double x=m_radius*(1.0-2.0*((static_cast<double>(rand()))/(static_cast<double>(RAND_MAX))));
	double y=m_radius*(1.0-2.0*((static_cast<double>(rand()))/(static_cast<double>(RAND_MAX))));
	double z=m_radius*(1.0-2.0*((static_cast<double>(rand()))/(static_cast<double>(RAND_MAX))));
	res=Vec3(x,y,z);
      } while (res.norm()>=m_radius);

      return m_center+res;
    }
