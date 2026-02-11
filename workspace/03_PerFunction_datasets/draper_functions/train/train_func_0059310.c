push_back(const Pointcloud& other)   {
    for (Pointcloud::const_iterator it = other.begin(); it != other.end(); it++) {
      points.push_back(point3d(*it));
    }
  }
