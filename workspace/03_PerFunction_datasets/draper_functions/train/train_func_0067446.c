ImplicitHydrogenCount() const
  {

    OBMol *mol = (OBMol*)((OBAtom*)this)->GetParent();
    if (mol && !mol->HasImplicitValencePerceived())
      atomtyper.AssignImplicitValence(*((OBMol*)((OBAtom*)this)->GetParent()));


    int impval = _impval - GetValence();


    int mult = GetSpinMultiplicity();
    if(mult==2)
      impval-=1;
    else if(mult==1 || mult==3)
      impval-=2;
    else if(mult>=4)
      impval -= mult-1;
    return((impval>0)?impval:0);
  }
