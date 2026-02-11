FindAminoAcidAtomType(PDBAtom *atom)
{

  if (atom->IsHetAtom()) return PDB_NULL_ATOM;


  PDBResidue *residue = atom->Residue();
  if (!residue) return PDB_NULL_ATOM;


  PDBAminoAcid *aminoacid = residue->AminoAcid();
  if (!aminoacid) return PDB_NULL_ATOM;


  for (int i = 0; i < aminoacid->NAtoms(); i++) {
    int type = PDBaminoacid_atom_offsets[aminoacid->ID()] + i;
    const PDBAminoAcidAtomData *data = &PDBaminoacid_atoms[type];
    assert(data->aminoacid_id == aminoacid->ID());
    if (!strcmp(atom->Name(), data->atom_name)) return type;
  }


  return PDB_NULL_ATOM;
}
