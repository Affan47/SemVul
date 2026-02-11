F4() {

  complex answer;

  if (mode == PimPimPip || mode == Pi0Pi0Pim)
    answer = 0;

  else if (mode == PimKmKp)
    answer = T(piM, piM, s1, rhoMv, rhoGv, rhoWv)
      * (T(piM, piM, s3, rhoMa, rhoGa, rhoWa)
	 - 0.2 * T(piM, kM, s2, kstarM, kstarG, kstarW)) * (1.25);

  else if (mode == PimK0bK0)
    answer = -T(piM, piM, s1, rhoMv, rhoGv, rhoWv)
      * (T(piM, piM, s3, rhoMa, rhoGa, rhoWa)
	 - 0.2 * T(piM, kM, s2, kstarM, kstarG, kstarW)) * (1.25);

  else if (mode == Pi0K0Km)
    answer = 0;

  else if (mode == Pi0Pi0Km)
    answer = 0;

  else if (mode == PimPipKm)
    answer = -T(piM, kM, s1, kstarM, kstarG, kstarW)
      * (T(piM, piM, s2, rhoMa, rhoGa, rhoWa)
	 - 0.2 * T(piM, kM, s3, kstarM, kstarG, kstarW)) * (1.25);

  else if (mode == Pi0PimK0b)
    answer = 2.0 * T(piM, kM, s1, kstarM, kstarG, kstarW)
      * (T(piM, piM, s3, rhoMa, rhoGa, rhoWa)
	 - 0.2 * T(piM, kM, s2, kstarM, kstarG, kstarW)) * (1.25);

  else if (mode == Pi0PimEta)
    answer = T(piM, piM, s1, rhoMv, rhoGv, rhoWv)
      * T(piM, piM, s4, rhoMa, rhoGa, rhoWa);
  return 1.0 / (4.0 * M_PI * M_PI * piW * piW) * answer;

}
