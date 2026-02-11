PDBBox(const RNArray<PDBAtom *>& atoms)
{

  R3Box bbox(R3null_box);
  for (int i = 0; i < atoms.NEntries(); i++)
    bbox.Union(atoms[i]->BBox());


  return bbox;
}
