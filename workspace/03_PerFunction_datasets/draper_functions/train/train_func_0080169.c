crop(point3d lowerBound, point3d upperBound) {


    for (ScanGraph::iterator it = this->begin(); it != this->end(); it++) {
      pose6d scan_pose = (*it)->pose;
      Pointcloud* pc = new Pointcloud((*it)->scan);
      pc->transformAbsolute(scan_pose);
      pc->crop(lowerBound, upperBound);
      pc->transform(scan_pose.inv());
      delete (*it)->scan;
      (*it)->scan = pc;
    }
  }
