doinitrun() {
  DecayIntegrator::doinitrun();
  for(unsigned int ix=0;ix<numberModes();++ix) {
    double fact = pow(1.5,int(mode(ix)->externalParticles(0)->iSpin())-1);
    mode(ix)->setMaxWeight(fact*mode(ix)->maxWeight());
  }
}
