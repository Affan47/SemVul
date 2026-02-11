get_mulliken_charges(const symmMatrix & densityMatrix,
		     const symmMatrix & S_symm,
		     const BasisInfoStruct & basisInfo,
		     mat::SizesAndBlocks const & matrix_size_block_info,
		     std::vector<int> const & permutationHML,
		     std::vector<int> const & inversePermutationHML,
		     const Molecule& molecule,
		     std::vector<ergo_real> & resultVector)
{
  int nAtoms = molecule.getNoOfAtoms();
  resultVector.resize(nAtoms);
  for(int i = 0; i < nAtoms; i++)
    resultVector[i] = 0;

  int n = basisInfo.noOfBasisFuncs;
  std::vector<int> atomMapping(n);
  for(int i = 0; i < n; i++) {

    int foundAtomIndex = -1;
    for(int k = 0; k < nAtoms; k++) {
      ergo_real dx = molecule.getAtom(k).coords[0] - basisInfo.basisFuncList[i].centerCoords[0];
      ergo_real dy = molecule.getAtom(k).coords[1] - basisInfo.basisFuncList[i].centerCoords[1];
      ergo_real dz = molecule.getAtom(k).coords[2] - basisInfo.basisFuncList[i].centerCoords[2];
      ergo_real distance = std::sqrt(dx*dx + dy*dy + dz*dz);
      if(distance < 1e-4)
	foundAtomIndex = k;
    }
    if(foundAtomIndex < 0)
      throw "Error in get_mulliken_charges: all basis functions are not centered on atoms.";
    atomMapping[i] = foundAtomIndex;
  }

  normalMatrix D(densityMatrix);
  normalMatrix S(S_symm);

  std::vector<int> rowind;
  std::vector<int> colind;
  std::vector<ergo_real> values_D;
  D.get_all_values(rowind,
		   colind,
		   values_D,
		   inversePermutationHML,
		   inversePermutationHML);
  int nvalues = values_D.size();


  std::vector<ergo_real> values_S(nvalues);
  for(int i = 0; i < nvalues; i++)
    values_S[i] = 0;
  S.get_values(rowind,
	       colind,
	       values_S,
	       permutationHML,
	       permutationHML);


  for(int i = 0; i < nvalues; i++) {
    int row = rowind[i];
    int col = colind[i];
    int atomIndex1 = atomMapping[row];
    int atomIndex2 = atomMapping[col];
    resultVector[atomIndex1] += 0.5 * values_D[i] * values_S[i];
    resultVector[atomIndex2] += 0.5 * values_D[i] * values_S[i];
  }
}
