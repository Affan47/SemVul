CreateVariable(struct FemType *data,int variable,int unknowns,
		   Real value,char *dofname,int eorder)

{
  int i,info=FALSE;
  int timesteps;

  if(variable == 0) return(0);

  if(data->created == FALSE) {
    if(info) printf("CreateVariable: Knots must first be created!\n");
    return(1);
  }
  timesteps = data->timesteps;
  if(timesteps < 1) timesteps = 1;

  if(data->edofs[variable] == 0) {

    data->variables += 1;
    data->edofs[variable] = unknowns;
    data->alldofs[variable] = unknowns * data->noknots;
    data->bandwidth[variable] = unknowns * data->indexwidth;
    data->dofs[variable]  = Rvector(1,timesteps * data->alldofs[variable]);
    if(info) printf("Created variable %s with %d dofs.\n",
		    dofname,data->alldofs[variable]);
    for(i=1;i<=data->alldofs[variable]*timesteps;i++)
      data->dofs[variable][i] = value;
    data->iterdofs[variable] = 1;
  }
  else if (data->edofs[variable] == unknowns) {
    if(info) printf("CreateVariable: Variable %d exists with correct number of dofs!\n",
		    variable);
  }
  else {
    if(info) printf("CreateVariable: Variable %d exists with wrong number of dofs!\n",
		    variable);
    return(2);
  }


  if(eorder) {
    if (data->eorder[variable] == FALSE) {
      data->eorder[variable] = TRUE;
      data->order[variable] = Ivector(1,data->alldofs[variable]);
      for(i=1;i<=data->alldofs[variable];i++)
	data->order[variable][i] = i;
    }
    if(info) printf("Created index for variable %s.\n",dofname);
  }

  strcpy(data->dofname[variable],dofname);

  return(0);
}
