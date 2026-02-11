RayHitSphere(
       Geometry_t *Geometry,double FX,double FY,double FZ,
           double DX,double DY,double DZ,double L
          )
{
     Sphere_t *Sph = Geometry->Sphere;

     double A,B,C,D,E,AC4,T,R=Sph->Radius,EPS=REPS;

     FX -= Sph->CenterPoint.x;
     FY -= Sph->CenterPoint.y;
     FZ -= Sph->CenterPoint.z;

     if (
            FX>R && FX+DX>R || FX<-R && FX+DX<-R ||
            FY>R && FY+DY>R || FY<-R && FY+DY<-R ||
            FZ>R && FZ+DZ>R || FZ<-R && FZ+DZ<-R
         ) return FALSE;

     A = DX*DX + DY*DY + DZ*DZ;
     if ( A<1.0E-12 ) return FALSE;

     B = 2*(FX*DX + FY*DY + FZ*DZ);
     C = FX*FX + FY*FY + FZ*FZ - R*R;

     if ( B>=0 && C>=0 ) return FALSE;

     if ( (D = B*B - 4*A*C)<0.0 ) return FALSE;

     D = sqrt(D);

     if ( B > 0 ) {
       T = -2*C/(B+D);
     } else {
       T = (-B+D)/(2*A);
     }
     if ( T>EPS && T<1-EPS ) return TRUE;

     if  ( B > 0 ) {
       T = -(B+D)/(2*A);
     } else {
       T = 2*C/(-B+D);
     }
     return T>EPS && T<1-EPS;
}
