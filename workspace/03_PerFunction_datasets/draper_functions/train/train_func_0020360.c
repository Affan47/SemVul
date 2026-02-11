getRegularBBoxVector() const
    {
      BoundingBoxVector bBoxVector;
      if (m_gougePrms.m_size + 2*m_faultPrms.m_size < getOrientationSize()) {
        bBoxVector.reserve(2);
        bBoxVector.push_back(
          cutFromCentre(
            -(m_gougePrms.m_size/2.0 + m_faultPrms.m_size),
            -getOrientationSize()/2.0
          )
        );
        bBoxVector.push_back(
          cutFromCentre(
            m_gougePrms.m_size/2.0 + m_faultPrms.m_size,
            getOrientationSize()/2.0
          )
        );
      }
      return bBoxVector;
    }
