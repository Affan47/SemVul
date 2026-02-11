compute(OBMol *mol, const std::vector<unsigned int> &symClasses,
        const Automorphisms &automorphisms)
    {
      if (DEBUG_INVERSIONS) cout << "ENTER StereoInverted::compute()" << endl;


      std::vector<unsigned int> canon_labels;
      CanonicalLabels(mol, symClasses, canon_labels, OBBitVec(), 5, true);


      std::vector<Entry> result;


      for (std::size_t i = 0; i < automorphisms.size(); ++i) {
        Entry entry;
        entry.p = automorphisms[i];

        if (DEBUG_INVERSIONS) cout << "----> Checking automorphism " << i+1 << endl;


        std::vector<OBAtom*>::iterator ia;
        for (OBAtom *atom = mol->BeginAtom(ia); atom; atom = mol->NextAtom(ia)) {

          if (!isPotentialTetrahedral(atom))
            continue;

          if (permutationInvertsTetrahedralCenter(automorphisms[i], atom, symClasses, canon_labels))
            entry.invertedAtoms.push_back(atom);
        }


        std::vector<OBBond*>::iterator ib;
        for (OBBond *bond = mol->BeginBond(ib); bond; bond = mol->NextBond(ib)) {

          if (!isPotentialCisTrans(bond))
            continue;

          if (permutationInvertsCisTransCenter(entry.p, bond, canon_labels))
            entry.invertedBonds.push_back(bond);
        }

        if (DEBUG_INVERSIONS) {
          cout << "automorphism " << i+1 << "     ";
          for (std::size_t j = 0; j < mol->NumAtoms(); ++j) {
            unsigned int t;
            if (MapsTo(entry.p, j, t)) {
              if (t < 10) {
                cout << " " << t << " ";
              } else {
                cout << t << " ";
              }
            }
          }
          cout << endl;
          cout << "  invertedAtoms: ";
          for (std::size_t l = 0; l < entry.invertedAtoms.size(); ++l)
            cout << entry.invertedAtoms[l]->GetId() << " ";
          cout << endl;
          cout << "  invertedBonds: ";
          for (std::size_t l = 0; l < entry.invertedBonds.size(); ++l)
            cout << entry.invertedBonds[l]->GetId() << " ";
          cout << endl;
        }

        result.push_back(entry);
      }

      if (DEBUG_INVERSIONS) cout << "EXIT StereoInverted::compute()" << endl;

      return result;
    }
