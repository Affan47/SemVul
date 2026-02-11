SwapTest( size_t in1, size_t in2, size_t io1, size_t io2 )
{


  double dx11 = theX[io1-1] - theX[in1-1];
  double dx12 = theX[io2-1] - theX[in1-1];
  double dx22 = theX[io2-1] - theX[in2-1];
  double dx21 = theX[io1-1] - theX[in2-1];

  double dy11 = theY[io1-1] - theY[in1-1];
  double dy12 = theY[io2-1] - theY[in1-1];
  double dy22 = theY[io2-1] - theY[in2-1];
  double dy21 = theY[io1-1] - theY[in2-1];


  double cos1 = dx11*dx12 + dy11*dy12;
  double cos2 = dx22*dx21 + dy22*dy21;


  if( cos1>=0. && cos2>=0. )return false;

  if( cos1<0. && cos2<0. )return true;


  double sin1 = dx11*dy12 - dx12*dy11;
  double sin2 = dx22*dy21 - dx21*dy22;
  if( sin1*cos2+cos1*sin2 >= 0. )return false;
  return true;
}
