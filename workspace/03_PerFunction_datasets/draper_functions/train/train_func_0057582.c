generate(int tries,unsigned int seed)
{
  srand(seed);

  int imin=int(floor(m_xmin/(m_rmax*2.0)));
  int jmin=int(floor(m_ymin/(m_rmax*sqrt(3.0))));
  int kmin=int(floor(m_zmin/(m_rmax*2.0*sqrt(2.0/3.0))));
  int imax=int(ceil(m_xmax/(m_rmax*2.0)));
  int jmax=int(ceil(m_ymax/(m_rmax*sqrt(3.0))));
  int kmax=int(ceil(m_zmax/(m_rmax*2.0*sqrt(2.0/3.0))));

  for(int i=imin;i<=imax;i++){
    for(int j=jmin;j<=jmax;j++){
      for(int k=kmin;k<kmax;k++){

	double r=m_random(m_rmin,m_rmax);

	double px=(double(i)+0.5*double(j%2)+0.5*double(k%2))*m_rmax*2.0;
	double py=(double(j)+double(k%2)/3.0)*sqrt(3.0)*m_rmax;
	double pz=(double(k)*2.0*sqrt(2.0/3.0))*m_rmax;
	SimpleParticle Po=SimpleParticle(Vec3(px,py,pz),r,getNParts());
	bool fit=checkAFit(Po);
	if(fit){
	  insertParticle(Po);
	}
      }
    }
  }

  fillSpace(tries);


  if(m_is_bonded){
    m_snt->getInteractions(m_iset,m_maxConnDist);
  }
}
