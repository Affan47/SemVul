single(int type, double rsq, int i, int j,
                          double &fforce)

{
  if (map[type] < 0) error->one(FLERR,"Invoked bond single on bond style none");
  return styles[map[type]]->single(type,rsq,i,j,fforce);
}
