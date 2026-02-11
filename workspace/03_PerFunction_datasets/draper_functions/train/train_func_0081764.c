ProceedReconstruction(Matches &matches,
                           Vec2 &image_size) {
  VLOG(1) << "Euclidean Reconstruction From Video..." << std::endl;
  std::list<Reconstruction *> reconstructions;
  EuclideanReconstructionFromVideo(matches,
                                   image_size(0),
                                   image_size(1),
                                   FLAGS_focal,
                                   &reconstructions);
  VLOG(1) << "Euclidean Reconstruction From Video...[DONE]" << std::endl;
  int i = 0;
  std::list<Reconstruction *>::iterator iter = reconstructions.begin();
  for (; iter != reconstructions.end(); ++iter) {
    std::stringstream s;
    if (reconstructions.size() > 1)
      s << "./out" << "-" << i << ".py";
    else
      s << "./out.py";
    ExportToBlenderScript(**iter, s.str());
  }

  VLOG(2) << "Cleaning." << std::endl;
  iter = reconstructions.begin();
  for (; iter != reconstructions.end(); ++iter) {
    (*iter)->ClearCamerasMap();
    (*iter)->ClearStructuresMap();
    delete *iter;
  }
  reconstructions.clear();
}
