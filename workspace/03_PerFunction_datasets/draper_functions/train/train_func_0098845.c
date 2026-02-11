create()
{


  if (cuda) comm = new CommCuda(this);
  else comm = new Comm(this);

  if (cuda) neighbor = new NeighborCuda(this);
  else neighbor = new Neighbor(this);

  if (cuda) domain = new DomainCuda(this);
#ifdef LMP_USER_OMP
  else domain = new DomainOMP(this);
#else
  else domain = new Domain(this);
#endif

  atom = new Atom(this);
  atom->create_avec("atomic",0,NULL,suffix);

  group = new Group(this);
  force = new Force(this);

  if (cuda) modify = new ModifyCuda(this);
  else modify = new Modify(this);

  output = new Output(this);

  update = new Update(this);
  timer = new Timer(this);
}
