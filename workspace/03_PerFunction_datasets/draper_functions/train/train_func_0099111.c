DetectGoodFeatures(const Array3Df &image_and_gradients,
                                    FeatureList *features) {
  Array3Df gradient_matrix;
  ComputeGradientMatrix(image_and_gradients, WindowSize(), &gradient_matrix);

  Array3Df trackness;
  double trackness_mean;
  ComputeTrackness(gradient_matrix, &trackness, &trackness_mean);
  min_trackness_ = trackness_mean;

  FindLocalMaxima(trackness, min_trackness_, features);

  RemoveTooCloseFeatures(features, min_feature_dist_ * min_feature_dist_);
}
