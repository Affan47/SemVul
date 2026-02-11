Detect(const Image &image,
                      vector<Feature *> *features,
                      DetectorData **data) {
    int num_corners = 0;
    ByteImage *byte_image = image.AsArray3Du();
    if (byte_image) {
      xy* detections = detector_(byte_image->Data(),
          byte_image->Width(), byte_image->Height(), byte_image->Width(),
          threshold_, &num_corners);

      for (int i = 0; i < num_corners; ++i) {
        PointFeature *f = new PointFeature(detections[i].x, detections[i].y);
        f->scale = 3.0;
        f->orientation = 0.0;
        features->push_back(f);
      }
      free( detections );

      if (bRotationInvariant_) {
        fastRotationEstimation(*byte_image,*features);

      }
    }
    else  {
      LOG(ERROR) << "Invalid input image type for FAST detector";
    }


    if (data) {
      *data = NULL;
    }
  }
