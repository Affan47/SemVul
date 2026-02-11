setInitialMeshH()
{
  UserInterface* ui = theControlCenter->getGui();

  double initial_mesh_h = calcInitialMeshH();

  if (initial_mesh_h < MAX_RANGE)
    ui->setInitialMeshH(initial_mesh_h);
  else
    ui->setInitialMeshH(-1.0);
}
