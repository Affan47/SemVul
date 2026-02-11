threeBodydGammads(const int imodeb,
							  const Energy2 q2,
							  const Energy2 mff2,
							  const Energy m1,
							  const Energy m2,
							  const Energy m3) const {

  Energy q=sqrt(q2);
  Energy2 m12=m1*m1;
  Energy2 m22=m2*m2;
  Energy2 m32=m3*m3;

  Complex ii(0.,1.);
  complex<InvEnergy3> pre = _coupling[imodeb] / mff2;

  if(_includeVMD[imodeb]>0) {
    Energy2 mrho2=_VMDmass[imodeb]*_VMDmass[imodeb];
    Energy2 mwrho=_VMDmass[imodeb]*_VMDwidth[imodeb];
    pre = pre*(-mrho2+ii*mwrho)/(mff2-mrho2+ii*mwrho);
  }
  InvEnergy6 factor=real(pre*conj(pre));

  Energy mff=sqrt(mff2);
  Energy e2star = 0.5*(mff2-m32+m22)/mff;
  Energy e1star = 0.5*(q2-mff2-m12)/mff;
  Energy e1sm = sqrt(e1star*e1star-m12);
  Energy e2sm = sqrt(e2star*e2star-m22);
  Energy2 a = 2*e1star*e2star+m12+m22;
  Energy2 b = 2*e1sm*e2sm;

  Energy8 me = 2*b*(2*(m12*(mff2*mff2 + 4*mff2*m2*m3 -(m22 - m32)*(m22 - m32)) +
		       2*m2*(m12 +m22)*m3*(-mff2 +m22 + q2))
		    +(m12 +m22)*(m12 +m22)*(-mff2 +m22 - 2*m2*m3 - m32)
		    -(mff2 +m22 + 2*m2*m3 - m32)*(-mff2 +m22 + q2)*(-mff2 +m22 + q2));

  me+= 2.*a*b*(2*(-mff2*mff2 - (m22 - m32)*(m12 - q2) +
		  mff2*(m12 + m22 + m32 + q2)));

  me+=-4.*mff2*b*(3.*a*a+b*b)/3.;


  using Constants::pi;
  return -factor * me/256./pi/pi/pi/q2/q;
}
