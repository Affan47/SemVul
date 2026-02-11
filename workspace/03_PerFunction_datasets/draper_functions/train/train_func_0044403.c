HasAlphaBetaUnsat(bool includePandS)
  {
    OBAtom *a1,*a2;
    OBBondIterator i,j;

    for (a1 = BeginNbrAtom(i);a1;a1 = NextNbrAtom(i))
      if (includePandS || (!a1->IsPhosphorus() && !a1->IsSulfur()))
        for (a2 = a1->BeginNbrAtom(j);a2;a2 = a1->NextNbrAtom(j))
          if (a2 != this && ((*j)->GetBO() == 2 || (*j)->GetBO() == 3 || (*j)->GetBO() == 5))
            return(true);

    return(false);
  }
