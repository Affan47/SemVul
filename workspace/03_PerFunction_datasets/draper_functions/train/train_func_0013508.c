encodePDS_ECMWF_local_Extension_1(GRIBPACK *lGrib, long *zs, int *isec1)
{

  long localextlen, i;
  long z = *zs;

  localextlen = getLocalExtLen(isec1);
  for ( i = 0; i < localextlen-12; i++ )
    {
      Put1Byte(isec1[24+i]);
    }

  Put1Byte(isec1[36]);

  Put1Byte(isec1[37]);
  Put1Byte(isec1[38]);
  Put2Byte(isec1[39]);


  Put1Byte(((unsigned char*) &isec1[40])[0]);
  Put1Byte(((unsigned char*) &isec1[40])[1]);
  Put1Byte(((unsigned char*) &isec1[40])[2]);
  Put1Byte(((unsigned char*) &isec1[40])[3]);

  Put1Byte(isec1[41]);
  Put1Byte(isec1[42]);
  Put1Byte(0);

  *zs = z;
}
