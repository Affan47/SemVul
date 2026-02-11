randomUnitVector(OBRandom *obRandP)
  {
    OBRandom *ptr;
    if (!obRandP)
      {
        ptr = new OBRandom(true);
        ptr->TimeSeed();
      }
    else
      ptr = obRandP;


    double l;
    do
      {
        this->Set(ptr->NextFloat()-0.5, ptr->NextFloat()-0.5, ptr->NextFloat()-0.5);
        l = length_2();
      }
    while ( (l > 1.0) || (l < 1e-4) );
    this->normalize();

    if (!obRandP)
      delete ptr;
  }
