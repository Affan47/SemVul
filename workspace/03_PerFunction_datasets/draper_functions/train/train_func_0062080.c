AddTwoVectorsImpl(Number a, const Vector& v1,
                                 Number b, const Vector& v2, Number c)
  {
    if (c==0.) {
      if (a==1.) {
        Copy(v1);
        if (b!=0.) {
          Axpy(b, v2);
        }
      }
      else if (a==0.) {
        if (b==0.) {
          Set(0.);
        }
        else {
          Copy(v2);
          if (b!=1.) {
            Scal(b);
          }
        }
      }
      else {
        if (b==1.) {
          Copy(v2);
          Axpy(a, v1);
        }
        else if (b==0.) {
          Copy(v1);
          Scal(a);
        }
        else {
          Copy(v1);
          Scal(a);
          Axpy(b, v2);
        }
      }
    }
    else {
      if (c!=1.) {
        Scal(c);
      }
      if (a!=0.) {
        Axpy(a, v1);
      }
      if (b!=0.) {
        Axpy(b, v2);
      }
    }
  }
