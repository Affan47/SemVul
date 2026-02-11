init(int myNumber, int Z, real thrl)
{
  static const real zetas[] =
    { 0.8,  0.9,
      1.8,  1.4,  1.3,   1.1,
      0.9,    0.9,  0.9,   0.9,
      1.4,  1.3,  1.3,  1.2,
      1.1,    1.0,  1.0,  1.0,
      1.5,   1.4,  1.3,  1.2,  1.2,
      1.2,  1.2,  1.2,  1.2,  1.1,
      1.1,  1.1,  1.1,  1.0,  0.9,
      0.9,  0.9,  0.9
    };

  int ta, accuracy_correction, z_correction;

  if(Z<=2) ta=0;
  else if(Z<=10) ta=1;
  else if(Z<=18) ta=2;
  else if(Z<=36) ta=3;
  else if(Z<=54) ta=4;
  else if(Z<=86) ta=5;
  else ta=6;


  accuracy_correction = int( (-std::log10(thrl)-5.0)*3.0 );
  if(accuracy_correction<0) accuracy_correction = 0;
  z_correction = ta*5;

  static const int MIN_RAD_PT = 20;

  gridSize = MIN_RAD_PT + accuracy_correction + z_correction;
  zeta = Z >=1 && Z <= int(sizeof(zetas)/sizeof(zetas[0]))
    ?  zetas[Z-1] : 0.9;
}
