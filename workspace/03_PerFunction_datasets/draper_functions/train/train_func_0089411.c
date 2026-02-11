reconstructParent(const tShowerParticlePtr theParent,
	     const ParticleVector & theChildren ) const {
  if(theChildren.size() != 2)
    throw Exception() << "FS_QTildeShowerKinematics1to2::updateParent() "
		      << "Warning! too many children!"
		      << Exception::eventerror;
  ShowerParticlePtr c1 = dynamic_ptr_cast<ShowerParticlePtr>(theChildren[0]);
  ShowerParticlePtr c2 = dynamic_ptr_cast<ShowerParticlePtr>(theChildren[1]);
  theParent->showerParameters()[1]=
    c1->showerParameters()[1] + c2->showerParameters()[1];
  theParent->set5Momentum( c1->momentum() + c2->momentum() );
}
