ExampleGrid1D(struct GridType **grids,int *nogrids,int info)


{
  int i,j;
  struct GridType *grid;

  (*nogrids) = 1;
  (*grids) = (struct GridType*)
    malloc((size_t) (*nogrids)*sizeof(struct GridType));

  grid = grids[0];

  InitGrid(grid);

  grid->nonodes = 2;
  grid->xcells = 3;
  grid->ycells = 1;
  grid->wantedelems = 40;
  grid->firstmaterial = 1;
  grid->lastmaterial = 1;
  grid->autoratio = 1;
  grid->coordsystem = COORD_CART1;
  grid->numbering = NUMBER_1D;

  grid->x[0] = 0.0;
  grid->x[1] = 1.0;
  grid->x[2] = 3.0;
  grid->x[3] = 4.0;

  grid->xexpand[1] = 2.0;
  grid->xexpand[3] = 0.5;
  grid->xdens[2] = 0.5;

  for(j=1;j<=3;j++)
    grid->structure[1][j] = 1;

  grid->noboundaries = 2;
  grid->boundint[0] = 1;
  grid->boundint[1] = 1;

  grid->boundext[0] = -1;
  grid->boundext[1] = -2;

  grid->boundtype[0] = 1;
  grid->boundtype[1] = 2;

  grid->boundsolid[0] = 1;
  grid->boundsolid[1] = 1;

  grid->mappings = 0;

  if(info) printf("A simple 1D example mesh was created\n");
}
