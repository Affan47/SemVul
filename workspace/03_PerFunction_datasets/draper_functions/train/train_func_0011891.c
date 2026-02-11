Evaluate(double uvw[3], double Pt[3], double Duvw[9])
{

  double u = uvw[0];
  double v = uvw[1];
  double *Du = Duvw;
  double *Dv = Duvw + 3;

  double cu = cos(u);
  double cv = cos(v);
  double su = sin(u);
  double sv = sin(v);


  Pt[0] = this->A*cu*sv;
  Pt[1] = this->A*su*sv;
  Pt[2] = this->A*(cos(v)+log(tan((v/2))))+this->B*u;


  Du[0] = -Pt[1];
  Dv[0] = this->A*cu*cv;
  Du[1] = Pt[0];
  Dv[1] = this->A*su*cv;
  Du[2] = this->B;
  double tv2 = tan(0.5*v);
  if ( tv2 != 0 )
     Dv[2] = this->A*(-sv+(0.5+0.5*tv2*tv2)/tv2);
  else
     Dv[2] = this->A*(-sv+(0.5+0.5*tv2*tv2)/0.0001);
}
