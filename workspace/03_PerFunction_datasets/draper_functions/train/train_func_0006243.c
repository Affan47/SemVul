Centroid(void) const
{

  int atom_count = 0;
  R3Point centroid(0, 0, 0);
  for (int i = 0; i < NModels(); i++) {
    PDBModel *model = Model(i);
    int natoms = model->NAtoms();
    centroid += natoms * model->Centroid();
    atom_count += natoms;
  }
  centroid /= atom_count;
  return centroid;
}
