getNormDevStress(const Tensor &stressTensor) const
    {
      StressTensor::ComplexVector eigenvals = stressTensor.getEigenvalues();
      std::sort(eigenvals.begin(), eigenvals.end(), NormComparer());

      return
        (
          is3d()
          ?
          std::norm(eigenvals[2] - eigenvals[0])
          :
          std::norm(eigenvals[2] - eigenvals[1])
        );
    }
