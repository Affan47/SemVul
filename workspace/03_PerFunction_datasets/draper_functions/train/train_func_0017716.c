initl
     (
       int satn,      gravconsttype whichconst,
       double ecco,   double epoch,  double inclo,   double& no,
       char& method,
       double& ainv,  double& ao,    double& con41,  double& con42, double& cosio,
       double& cosio2,double& eccsq, double& omeosq, double& posq,
       double& rp,    double& rteosq,double& sinio , double& gsto,
       char opsmode
     )
{
     UNUSED( satn );

     double ak, d1, del, adel, po, x2o3, j2, xke,
            tumin, mu, radiusearthkm, j3, j4, j3oj2;


     double ds70;
     double ts70, tfrac, c1, thgr70, fk5r, c1p2p;
     const double twopi = 2.0 * M_PI;


     getgravconst( whichconst, tumin, mu, radiusearthkm, xke, j2, j3, j4, j3oj2 );
     x2o3   = 2.0 / 3.0;


     eccsq  = ecco * ecco;
     omeosq = 1.0 - eccsq;
     rteosq = sqrt(omeosq);
     cosio  = cos(inclo);
     cosio2 = cosio * cosio;


     ak    = pow(xke / no, x2o3);
     d1    = 0.75 * j2 * (3.0 * cosio2 - 1.0) / (rteosq * omeosq);
     del   = d1 / (ak * ak);
     adel  = ak * (1.0 - del * del - del *
             (1.0 / 3.0 + 134.0 * del * del / 81.0));
     del   = d1/(adel * adel);
     no    = no / (1.0 + del);

     ao    = pow(xke / no, x2o3);
     sinio = sin(inclo);
     po    = ao * omeosq;
     con42 = 1.0 - 5.0 * cosio2;
     con41 = -con42-cosio2-cosio2;
     ainv  = 1.0 / ao;
     posq  = po * po;
     rp    = ao * (1.0 - ecco);
     method = 'n';


     if (opsmode == 'a')
        {


         ts70  = epoch - 7305.0;
         ds70 = floor(ts70 + 1.0e-8);
         tfrac = ts70 - ds70;

         c1    = 1.72027916940703639e-2;
         thgr70= 1.7321343856509374;
         fk5r  = 5.07551419432269442e-15;
         c1p2p = c1 + twopi;
         gsto  = fmod( thgr70 + c1*ds70 + c1p2p*tfrac + ts70*ts70*fk5r, twopi);
         if ( gsto < 0.0 )
             gsto = gsto + twopi;
       }
       else
        gsto = gstime(epoch + 2433281.5);


}
