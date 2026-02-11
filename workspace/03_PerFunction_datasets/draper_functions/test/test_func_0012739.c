cameraFocal(double lm)

{
   double nfk=0.;


   lm /= uves_air_index(lm);

   if (uves_arm_id == 'b' ) {

    nfk=5.3961886e-7*lm*lm*lm-0.00079597882*lm*lm+0.41122805*lm+287.89644;
   }

   if (uves_arm_id == 'r' ) {

    nfk=6.0172051e-13*lm*lm*lm*lm*lm-2.5623231e-9*lm*lm*lm*lm+
        4.3585543e-6*lm*lm*lm -0.0037286381*lm*lm+
        1.6289971*lm + 210.06767;

   }


return(nfk/1000.);

}
