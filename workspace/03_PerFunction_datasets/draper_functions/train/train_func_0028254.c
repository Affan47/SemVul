Detect(const Image &image,
                      vector<Feature *> *features,
                      DetectorData **data) {
    ByteImage *byte_image = image.AsArray3Du();


    Matu integral_image;
    IntegralImage(*byte_image, &integral_image);

    libmv::vector<PointFeature> detections;
    MultiscaleDetectFeatures(integral_image, num_octaves_, num_intervals_,
                           &detections);

    for (int i = 0; i < detections.size(); ++i) {
      PointFeature *f = new PointFeature(detections[i].x(), detections[i].y());
      f->scale = detections[i].scale;
      f->orientation = detections[i].orientation;
      features->push_back(f);
    }


    if (data) {
      *data = NULL;
    }
  }
