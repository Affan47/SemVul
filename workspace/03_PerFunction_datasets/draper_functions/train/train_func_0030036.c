UpgradeToMetric(const Matches &matches,
                     Reconstruction *reconstruction) {
  double rms = EstimateRootMeanSquareError(matches, reconstruction);
  VLOG(1)   << "Upgrade to Metric - Initial RMS:" << rms << std::endl;
  AutoCalibrationLinear auto_calibration_linear;
  uint image_width = 0;
  uint image_height = 0;
  PinholeCamera * pcamera = NULL;
  std::map<CameraID, Camera *>::iterator camera_iter =
    reconstruction->cameras().begin();
  for (; camera_iter != reconstruction->cameras().end(); ++camera_iter) {
    pcamera = dynamic_cast<PinholeCamera *>(camera_iter->second);
    if (pcamera) {
      image_width = pcamera->image_width();
      image_height = pcamera->image_height();


      if (!image_width  && !image_height) {
        image_width  = 640;
        image_height = 480;
      }
      auto_calibration_linear.AddProjection(pcamera->projection_matrix(),
                                            image_width, image_height);
    }
  }


  Mat4 H = auto_calibration_linear.MetricTransformation();
  VLOG(1)   << "Rectification H = " << H << "\n";
  if (isnan(H.sum())) {
    LOG(ERROR) << "Warning: The metric rectification cannot be applied, the "
               << "matrix contains NaN values.\n";
    return false;
  }
  Mat34 P;
  camera_iter = reconstruction->cameras().begin();
  for (; camera_iter != reconstruction->cameras().end(); ++camera_iter) {
    pcamera = dynamic_cast<PinholeCamera *>(camera_iter->second);
    if (pcamera) {
      P = pcamera->projection_matrix() * H;
      pcamera->set_projection_matrix(P);
      P_From_KRt(pcamera->intrinsic_matrix(),
                 pcamera->orientation_matrix(),
                 pcamera->position(), &P);

      pcamera->set_projection_matrix(P);
    }
  }
  Mat4 H_inverse = H.inverse();
  PointStructure * pstructure = NULL;
  std::map<StructureID, Structure *>::iterator stucture_iter =
    reconstruction->structures().begin();
  for (; stucture_iter != reconstruction->structures().end(); ++stucture_iter) {
    pstructure = dynamic_cast<PointStructure *>(stucture_iter->second);
    if (pstructure) {
      pstructure->set_coords(H_inverse * pstructure->coords());
    }
  }
  MetricBundleAdjust(matches, reconstruction);
  return true;
}
