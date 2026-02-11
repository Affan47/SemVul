CreateNewClassVector(OBMol *mol, std::vector<std::pair<OBAtom*,unsigned int> > &vp1,
      std::vector<std::pair<OBAtom*,unsigned int> > &vp2)
  {
    int m,id;
    OBAtom *atom, *nbr;
    vector<OBEdgeBase*>::iterator nbr_iter;
    vector<unsigned int>::iterator k;
    vector<pair<OBAtom*,unsigned int> >::iterator vp_iter;

#if DEBUG2
    cout << "CreateNewClassVector: START\n";

#endif


    vector<int> idx2index(mol->NumAtoms() + 1, -1);
    int index = 0;
    for (vp_iter = vp1.begin(); vp_iter != vp1.end(); ++vp_iter) {
      int idx = vp_iter->first->GetIdx();
      idx2index[idx] = index++;
    }


    vp2.resize(vp1.size());
    vp2.clear();


    for (vp_iter = vp1.begin(); vp_iter != vp1.end(); ++vp_iter) {
      atom = vp_iter->first;
      id   = vp_iter->second;
      vector<unsigned int> vtmp;
      for (nbr = atom->BeginNbrAtom(nbr_iter); nbr; nbr = atom->NextNbrAtom(nbr_iter)) {
        int idx = nbr->GetIdx();
        vtmp.push_back(vp1[idx2index[idx]].second);
      }

      sort(vtmp.begin(),vtmp.end(),CompareUnsigned);
      for (m = 100, k = vtmp.begin(); k != vtmp.end(); ++k, m*=100)
        id += *k * m;
      vp2.push_back(pair<OBAtom*,unsigned int> (atom, id));
    }
#if DEBUG2
    cout << "CreateNewClassVector: FINISH\n";

#endif

  }
