containsAtLeast_2true_2paraAssemblies(OBAtom *ligandAtom, OBAtom *atom, const OBStereoUnitSet &units, const std::vector<OBBitVec> &mergedRings)
  {
    OBMol *mol = atom->GetParent();


    OBBitVec ligand = getFragment(ligandAtom, atom);
    int trueStereoCenterCount = 0;
    std::vector<unsigned int> ringIndices;
    for (OBStereoUnitSet::const_iterator u2 = units.begin(); u2 != units.end(); ++u2) {
      if ((*u2).type == OBStereo::Tetrahedral) {
        if (ligand.BitIsOn((*u2).id)) {
          if ((*u2).para) {
            OBAtom *paraAtom = mol->GetAtomById((*u2).id);
            for (std::size_t ringIdx = 0; ringIdx < mergedRings.size(); ++ringIdx) {
              if (mergedRings.at(ringIdx).BitIsOn(paraAtom->GetIdx()))
                if (std::find(ringIndices.begin(), ringIndices.end(), ringIdx) == ringIndices.end())
                  ringIndices.push_back(ringIdx);
            }
          } else
            trueStereoCenterCount++;
        }
      } else if((*u2).type == OBStereo::CisTrans) {
        OBBond *bond = mol->GetBondById((*u2).id);
        OBAtom *begin = bond->GetBeginAtom();
        OBAtom *end = bond->GetEndAtom();
        if (ligand.BitIsOn(begin->GetId()) || ligand.BitIsOn(end->GetId())) {
          if ((*u2).para) {
            for (std::size_t ringIdx = 0; ringIdx < mergedRings.size(); ++ringIdx) {
              if (mergedRings.at(ringIdx).BitIsOn(begin->GetIdx()) || mergedRings.at(ringIdx).BitIsOn(end->GetIdx())) {
                if (std::find(ringIndices.begin(), ringIndices.end(), ringIdx) == ringIndices.end()) {
                  ringIndices.push_back(ringIdx);
                }
              }
            }
          } else {
            trueStereoCenterCount++;
          }
        }
      }
    }

    if (trueStereoCenterCount >= 2 || ringIndices.size() >= 2)
      return true;
    return false;
  }
