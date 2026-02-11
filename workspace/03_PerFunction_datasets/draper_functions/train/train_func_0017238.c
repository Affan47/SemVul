IsGood(const OBMol &mol, const RotorKey &key, double *conformer)
  {
    unsigned int a1 = 0, a2 = 0;
    unsigned int numAtoms = mol.NumAtoms();
    OBAtom *atom1 = NULL, *atom2 = NULL;
    double dx = 0.0, dy = 0.0, dz = 0.0;
    double distanceSquared = 0.0, vdwCutoff = 0.0;

    for (a1 = 0; a1 < numAtoms; ++a1) {
      for (a2 = a1 + 1; a2 < numAtoms; ++a2) {
        atom1 = mol.GetAtom(a1+1);
        atom2 = mol.GetAtom(a2+1);

	if (!m_check_hydrogens  && (atom1->IsHydrogen() || atom2->IsHydrogen() ))
    	  continue;


        if (atom1->IsConnected(atom2))
          continue;

        dx = conformer[a1*3  ] - conformer[a2*3  ];
        dy = conformer[a1*3+1] - conformer[a2*3+1];
        dz = conformer[a1*3+2] - conformer[a2*3+2];
        distanceSquared = dx*dx + dy*dy + dz*dz;


        vdwCutoff = m_vdw_factor * (etab.GetVdwRad(atom1->GetAtomicNum())
				  + etab.GetVdwRad(atom2->GetAtomicNum()));
        vdwCutoff *= vdwCutoff;


        if (distanceSquared < m_cutoff || distanceSquared < vdwCutoff)
          return false;
      }
    }

    return true;
  }
