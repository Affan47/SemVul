reconstructParent(const tShowerParticlePtr theParent,
		  const ParticleVector & theChildren ) const {
  ShowerParticlePtr c1 = dynamic_ptr_cast<ShowerParticlePtr>(theChildren[0]);
  ShowerParticlePtr c2 = dynamic_ptr_cast<ShowerParticlePtr>(theChildren[1]);


  c2->showerParameters()[1]=
    0.5*(sqr(c2->data().constituentMass())+sqr(c2->showerVariables()[2]))
    /(c2->showerParameters()[0]*p_dot_n());
  c2->set5Momentum(sudakov2Momentum(c2->showerParameters()[0],
				    c2->showerParameters()[1],
				    c2->showerVariables()[0],
				    c2->showerVariables()[1],0));

  Lorentz5Momentum pc1(theParent->momentum() - c2->momentum());
  pc1.rescaleMass();
  c1->set5Momentum(pc1);
}
