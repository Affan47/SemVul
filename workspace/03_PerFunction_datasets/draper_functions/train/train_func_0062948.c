doinit() {
  MassGenerator::doinit();

  particle_->init();
  widthGen_=particle_->widthGenerator();
  if(widthGen_){widthGen_->init();}

  mass_=particle_->mass();
  width_= widthOpt_ ? particle_->generateWidth(mass_) : particle_->width();
  mass2_=mass_*mass_;
  mWidth_=mass_*width_;
  lowerMass_ = mass_-particle_->widthLoCut();
  upperMass_ = mass_+particle_->widthUpCut();

  if(initialize_) {

    maxWgt_=0.;

    double wgt=0.,swgt=0.,sqwgt=0.;

    for(int ix=0;ix<nInitial_;++ix) {
      mass(wgt,*particle_,3);
      swgt  += wgt;
      sqwgt += sqr(wgt);
      if(wgt>maxWgt_) maxWgt_=wgt;
    }
    swgt=swgt/nInitial_;
    sqwgt=sqrt(max(0.,sqwgt/nInitial_-swgt*swgt)/nInitial_);
  }
}
