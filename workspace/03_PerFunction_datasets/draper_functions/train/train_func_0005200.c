build_topology()
{
  if (force->bond) (this->*bond_build)();
  if (force->angle) (this->*angle_build)();
  if (force->dihedral) (this->*dihedral_build)();
  if (force->improper) (this->*improper_build)();
}
