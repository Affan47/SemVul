transpose() {
   if (dim1 == dim2) {
      for (int i = 0; i < dim1; i++)
         for (int j = i+1; j < dim2; j++) {
            double t = _rep[i*dim2 + j];
            _rep[i*dim2 + j] = _rep[j*dim1 + i];
            _rep[j*dim1 + i] = t;
         }
   } else {
      int d = dim1;
      dim1 = dim2;
      dim2 = d;
      double *r = _rep;
      _rep = new double[dim1*dim2];
      for (int i = 0; i < dim1; i++)
         for (int j = 0; j < dim2; j++)
            _rep[i*dim2 + j] = r[j*dim1 + i];
   }
   return *this;
}
