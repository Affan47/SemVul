getVectorFieldFunction(const string& name)
{
  CRotBondedInteraction::VectorFieldFunction vf;

  if (name=="force"){
    vf=&CRotBondedInteraction::getForce;
  } else if (name=="normal_force"){
    vf=&CRotBondedInteraction::getNormalForce;
  } else if (name=="tangential_force"){
    vf=&CRotBondedInteraction::getTangentialForce;
  } else {
    vf=NULL;
    cerr << "ERROR - invalid name for interaction vector  access function" << endl;
  }

  return vf;
}
