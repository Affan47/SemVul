rhoKBreitWigner(Energy2 q2,unsigned int itype,
							 unsigned int ires) const {
  Energy q(sqrt(q2)),mass,width,mout[2]={_mpi,_mpi};

  if(itype==0) {
    mass=_rhoF123masses[ires];
    width=_rhoF123widths[ires];
  }
  else if(itype==1) {
    mass=_rhoF5masses[ires];
    width=_rhoF5widths[ires];
  }
  else if(itype==2) {
    mass=_kstarF123masses[ires];
    width=_kstarF123widths[ires];
  }
  else if(itype==3) {
    mass=_kstarF5masses[ires];
    width=_kstarF5widths[ires];
  }
  else {
    return 0.;
  }

  if(itype>1) mout[0]=_mK;
  Energy pcm0(Kinematics::pstarTwoBodyDecay(mass,mout[0],mout[1]));
  Energy pcm(ZERO);
  if(mout[0]+mout[1]<q){pcm=Kinematics::pstarTwoBodyDecay(q,mout[0],mout[1]);}
  double ratio = Math::Pow<3>(pcm/pcm0);
  Energy gamrun(width*mass*ratio/q);
  Complex ii(0.,1.);
  complex<Energy2> denom(q2-mass*mass+ii*mass*gamrun), numer(-mass*mass);
  return numer/denom;
}
