calculate_shape_function_2d_tri()
{
  int ife;
  double y1,y2, y3;
  get_tri_rule_pts_and_weight();

  for (ife=0; ife<totalNumberGaussPts; ife++)
    {
      y1 =  y1Area[ife];
      y2 =  y2Area[ife];
      y3 = 1.0 -y1 -y2;

      shapeFunction[ife][0] = y1*(2.*y1-1.);
      shapeFunction[ife][1] = y2*(2.*y2-1.);
      shapeFunction[ife][2] = y3*(2.*y3-1.);

      shapeFunction[ife][3] = 4.*y1*y2;
      shapeFunction[ife][4] = 4.*y2*y3;
      shapeFunction[ife][5] = 4.*y1*y3;


      dndy1GaussPts[ife][0] = 4*y1-1.;
      dndy1GaussPts[ife][1] = 0;
      dndy1GaussPts[ife][2] = 1-4.*y3;

      dndy1GaussPts[ife][3] = 4.*y2;
      dndy1GaussPts[ife][4] = -4.*y2;
      dndy1GaussPts[ife][5] = 4.*(1-2*y1-y2);

      dndy2GaussPts[ife][0] = 0.0;
      dndy2GaussPts[ife][1] = 4.*y2-1.;
      dndy2GaussPts[ife][2] = 1-4.*y3;

      dndy2GaussPts[ife][3] = 4.*y1;
      dndy2GaussPts[ife][4] = 4.*(1-y1-2.*y2);
      dndy2GaussPts[ife][5] = -4.*y1;
    }
}
