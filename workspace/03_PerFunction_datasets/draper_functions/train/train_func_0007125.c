GetSymmetry(std::vector<unsigned int> &symmetry_classes)
  {
    ClearSymmetry();


    OBPairData *pd = dynamic_cast<OBPairData*>(d->_pmol->GetData("OpenBabel Symmetry Classes"));

    int nclasses = 0;
    if (!pd) {
      nclasses = d->CalculateSymmetry(symmetry_classes);
    } else {
      istringstream iss(pd->GetValue());
      symmetry_classes.clear();
      copy(istream_iterator<unsigned int>(iss),
           istream_iterator<unsigned int>(),
           back_inserter<vector<unsigned int> >(symmetry_classes));

      vector<unsigned int> copy_sym = symmetry_classes;
      sort(copy_sym.begin(), copy_sym.end());
      vector<unsigned int>::iterator end_pos = unique(copy_sym.begin(), copy_sym.end());
      nclasses = end_pos - copy_sym.begin();
    }

    return nclasses;
  }
