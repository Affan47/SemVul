kernelinterpolation_1d(const ColumnVector& data, float index)
  {
    ColumnVector userkernel = sinckernel1D("hanning", 7, 1201);
    return kernelinterpolation_1d(data, index, userkernel, 7);
  }
