createFaultBlockGenerators()
    {
      PackingInfoVector packingInfoVector = m_prms.getFaultPackingInfoVector();
      for (
        PackingInfoVector::const_iterator it = packingInfoVector.begin();
        it != packingInfoVector.end();
        it++
      ) {
        GeneratorPtr genPtr =
          GeneratorPtr(
            new RandomBlockGenerator(
              *(m_nTablePtr.get()),
              *(m_particlePoolPtr.get()),
              it->getBBox(),
              it->getPeriodicDimensions(),
              m_prms.getTolerance(),
              it->getMinRadius(),
              it->getMaxRadius(),
              it->getFitPlaneVector(),
              m_prms.getMaxInsertionFailures()
            )
          );
        m_genPtrVector.push_back(genPtr);
        m_faultGenPtrVector.push_back(genPtr);
      }
    }
