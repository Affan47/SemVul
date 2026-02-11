F2() {

  complex answer(0,0);


  if (mode == PimPimPip) {
    for (unsigned int i = 0; i  < rhoM.size(); i++) {
      answer += -rhoWp[i] * pBreitWigner(pM[2], pM[4], s3, rhoM[i], rhoG[i])
	- rhoWd[i] / 3.0 * pBreitWigner(pM[3], pM[4], s2, rhoM[i], rhoG[i])
        * (s3 - s4);
    }
    answer += -2.0 / 3.0 * (sigW * sBreitWigner(pM[3], pM[4], s2, sigM, sigG)
      + f0W * sBreitWigner(pM[3], pM[4], s2, f0M, f0G));
    answer += f2W * (0.5 * (s4 - s2)
      * dBreitWigner(pM[2], pM[4], s3, f2M, f2G)
      - 1.0 / (18 * s2) * (4 * pow2(pM[2]) - s2) * (s1 + s2 - pow2(pM[2]))
      * dBreitWigner(pM[3], pM[4], s2, f2M, f2G));
  }


  else {
    for (unsigned int i = 0; i < rhoM.size(); i++) {
	answer += -rhoWp[i] / 3.0 *
	  pBreitWigner(pM[2], pM[4], s3, rhoM[i], rhoG[i]) -
	  rhoWd[i] * pBreitWigner(pM[3], pM[4], s2, rhoM[i], rhoG[i]) *
	  (s4 - s3 - pow2(pM[4]) + pow2(pM[3]));
    }
    answer += 2.0 / 3.0 * (sigW * sBreitWigner(pM[2], pM[3], s4, sigM, sigG)
			     + f0W * sBreitWigner(pM[2], pM[3], s4, f0M, f0G));
    answer += f2W / (18 * s4) * (s1 - pow2(pM[4]) + s4) *
	(4 * pow2(pM[2]) - s4) * dBreitWigner(pM[2], pM[3], s4, f2M, f2G);
  }
  return -a1BW * answer;

}
