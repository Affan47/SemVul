reset_atom2body()
{
  int iowner;


  int nlocal = atom->nlocal;

  for (int i = 0; i < nlocal; i++) {
    atom2body[i] = -1;
    if (bodytag[i]) {
      iowner = atom->map(bodytag[i]);
      if (iowner == -1) {
        char str[128];
        sprintf(str,
                "Rigid body atoms %d %d missing on proc %d at step "
                BIGINT_FORMAT,
                atom->tag[i],bodytag[i],comm->me,update->ntimestep);
        error->one(FLERR,str);

      }
      atom2body[i] = bodyown[iowner];
    }
  }
}
