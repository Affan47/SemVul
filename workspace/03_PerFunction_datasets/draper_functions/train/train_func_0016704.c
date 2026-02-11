createRegularBlockGenerators()
    {
      BoundingBoxVector bBoxVector = m_prms.getRegularBBoxVector();
      for (
        BoundingBoxVector::const_iterator it = bBoxVector.begin();
        it != bBoxVector.end();
        it++
      ) {
	std::cout << "regular block bounding box is :" << *it << std::endl;
        GeneratorPtr genPtr =
          GeneratorPtr(
            new RegularBlockGenerator(
              *(m_nTablePtr.get()),
              *(m_particlePoolPtr.get()),
              *it,
              m_prms.getPeriodicDimensions(),
              m_prms.getTolerance(),
              m_prms.getRegularBlockRadius()
            )
          );
        m_genPtrVector.push_back(genPtr);
        m_regularGenPtrVector.push_back(genPtr);
      }
    }
