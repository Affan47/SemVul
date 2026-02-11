trace() const
  {
    float tr = 0.0;
    for(int k = 1; k<=Nrows(); k++)
      {
	tr += (*this)(k,k);
      }

    return tr;
  }
