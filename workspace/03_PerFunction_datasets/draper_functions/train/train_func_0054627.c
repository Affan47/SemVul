initTuneEE( int eeTune) {


  if (eeTune != 0) resetTuneEE();


  if (eeTune == 1) {
    parm("StringFlav:probStoUD",     0.30  );
    parm("StringFlav:probQQtoQ",     0.10  );
    parm("StringFlav:probSQtoQQ",    0.40  );
    parm("StringFlav:probQQ1toQQ0",  0.05  );
    parm("StringFlav:mesonUDvector", 1.00  );
    parm("StringFlav:mesonSvector",  1.50  );
    parm("StringFlav:mesonCvector",  2.50  );
    parm("StringFlav:mesonBvector",  3.00  );
    parm("StringFlav:etaSup",        1.00  );
    parm("StringFlav:etaPrimeSup",   0.40  );
    parm("StringFlav:popcornSpair",  0.50  );
    parm("StringFlav:popcornSmeson", 0.50  );
    parm("StringZ:aLund",            0.30  );
    parm("StringZ:bLund",            0.58  );
    parm("StringZ:rFactB",           1.00  );
    parm("StringPT:sigma",           0.36  );
    parm("TimeShower:alphaSvalue",   0.137 );
    parm("TimeShower:pTmin",         0.5   );
    parm("TimeShower:pTminChgQ",     0.5   );
  }


  else if (eeTune == 2) {
    parm("StringFlav:probStoUD",     0.22  );
    parm("StringFlav:probQQtoQ",     0.08  );
    parm("StringFlav:probSQtoQQ",    0.75  );
    parm("StringFlav:probQQ1toQQ0",  0.025 );
    parm("StringFlav:mesonUDvector", 0.5   );
    parm("StringFlav:mesonSvector",  0.6   );
    parm("StringFlav:mesonCvector",  1.5   );
    parm("StringFlav:mesonBvector",  2.5   );
    parm("StringFlav:etaSup",        0.60  );
    parm("StringFlav:etaPrimeSup",   0.15  );
    parm("StringFlav:popcornSpair",  1.0   );
    parm("StringFlav:popcornSmeson", 1.0   );
    parm("StringZ:aLund",            0.76  );
    parm("StringZ:bLund",            0.58  );
    parm("StringZ:rFactB",           1.00  );
    parm("StringPT:sigma",           0.36  );
    parm("TimeShower:alphaSvalue",   0.137 );
    parm("TimeShower:pTmin",         0.5   );
    parm("TimeShower:pTminChgQ",     0.5   );
  }


  else if (eeTune == 3) {
    parm("StringFlav:probStoUD",     0.19  );
    parm("StringFlav:probQQtoQ",     0.09  );
    parm("StringFlav:probSQtoQQ",    1.00  );
    parm("StringFlav:probQQ1toQQ0",  0.027 );
    parm("StringFlav:mesonUDvector", 0.62  );
    parm("StringFlav:mesonSvector",  0.725 );
    parm("StringFlav:mesonCvector",  1.06  );
    parm("StringFlav:mesonBvector",  3.0   );
    parm("StringFlav:etaSup",        0.63  );
    parm("StringFlav:etaPrimeSup",   0.12  );
    parm("StringFlav:popcornSpair",  0.5   );
    parm("StringFlav:popcornSmeson", 0.5   );
    parm("StringZ:aLund",            0.3   );
    parm("StringZ:bLund",            0.8   );
    parm("StringZ:rFactB",           0.67  );
    parm("StringPT:sigma",           0.304 );
    parm("TimeShower:alphaSvalue",   0.1383);
    parm("TimeShower:pTmin",         0.4   );
    parm("TimeShower:pTminChgQ",     0.4   );
  }

}
