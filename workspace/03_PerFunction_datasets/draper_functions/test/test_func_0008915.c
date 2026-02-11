transposed()const
  {
    Matrix ret(getWidth(),getHeight());
    for(int i=0;i<getHeight();i++)
      for(int j=0;j<getWidth();j++)
	ret[j][i]=(*this)[i][j];
    return ret;
  }
