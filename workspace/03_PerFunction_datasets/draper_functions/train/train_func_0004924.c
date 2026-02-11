Describe(const vector<Feature *> &features,
                        const Image &image,
                        const detector::DetectorData *detector_data,
                        vector<Descriptor *> *descriptors) {
    (void) detector_data;

    daisy desc;


    desc.set_parameters(15, 3, 8, 8);


    ByteImage *byte_image = image.AsArray3Du();
    desc.set_image(byte_image->Data(),
                   byte_image->Height(),
                   byte_image->Width());


    desc.initialize_single_descriptor_mode();

    descriptors->resize(features.size());
    for (int i = 0; i < features.size(); ++i) {
      PointFeature *point = dynamic_cast<PointFeature *>(features[i]);
      VecfDescriptor *descriptor = NULL;
      if (point) {
        descriptor = new VecfDescriptor(desc.descriptor_size());
        desc.get_descriptor(point->y(),
                            point->x(),
                            point->orientation * 180.0 / 3.14159f,
                            descriptor->coords.data());
      }
      (*descriptors)[i] = descriptor;
    }
  }
