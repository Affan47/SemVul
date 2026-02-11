SDPConeVecNormalize(SDPConeVec V){
  int info;
  double vnorm;
  info = SDPConeVecNorm2(V,&vnorm);DSDPCHKERR(info);
  if (vnorm==0){ return 1;}
  vnorm=1.0/(vnorm);
  info = SDPConeVecScale(vnorm,V);DSDPCHKERR(info);
  return 0;
}
