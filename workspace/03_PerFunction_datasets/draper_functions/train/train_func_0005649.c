allocate()
{
  allocated = 1;
  int n = atom->ntypes;

  memory->create(setflag,n+1,n+1,"paircg:setflag");
  memory->create(cg_type,n+1,n+1,"paircg:cg_type");
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      setflag[i][j] = 0;
      cg_type[i][j] = CG_NOT_SET;
    }
  }

  memory->create(cut,n+1,n+1,"paircg:cut");
  memory->create(cutsq,n+1,n+1,"paircg:cutsq");
  memory->create(epsilon,n+1,n+1,"paircg:epsilon");
  memory->create(sigma,n+1,n+1,"paircg:sigma");
  memory->create(offset,n+1,n+1,"paircg:offset");

  memory->create(lj1,n+1,n+1,"paircg:lj1");
  memory->create(lj2,n+1,n+1,"paircg:lj2");
  memory->create(lj3,n+1,n+1,"paircg:lj3");
  memory->create(lj4,n+1,n+1,"paircg:lj4");
}
