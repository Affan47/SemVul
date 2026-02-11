allocate()
{
  allocated = 1;
  int n = atom->ntypes;

  memory->create(setflag,n+1,n+1,"pair:setflag");
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
      setflag[i][j] = 0;

  memory->create(cutsq,n+1,n+1,"pair:cutsq");

  map = new int[n+1];
  for (int i = 1; i <= n; i++) map[i] = -1;

  memory->create(type2Fij,n+1,n+1,"pair:type2Fij");
  memory->create(type2Gij,n+1,n+1,"pair:type2Gij");
  memory->create(type2phiij,n+1,n+1,"pair:type2phiij");
}
