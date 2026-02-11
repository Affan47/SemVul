allocate()
{
  allocated = 1;
  int n = atom->ntypes;

  memory->create(setflag,n+1,n+1,"pair:setflag");
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
      setflag[i][j] = 0;

  memory->create(cutsq,n+1,n+1,"pair:cutsq");

  memory->create(z,n+1,"pair:z");
  memory->create(d1a,n+1,n+1,"pair:d1a");
  memory->create(d2a,n+1,n+1,"pair:d2a");
  memory->create(d3a,n+1,n+1,"pair:d3a");
  memory->create(d4a,n+1,n+1,"pair:d4a");
  memory->create(zze,n+1,n+1,"pair:zze");
  memory->create(sw1,n+1,n+1,"pair:sw1");
  memory->create(sw2,n+1,n+1,"pair:sw2");
  memory->create(sw3,n+1,n+1,"pair:sw3");
  memory->create(sw4,n+1,n+1,"pair:sw4");
  memory->create(sw5,n+1,n+1,"pair:sw5");
}
