_dxfQuads2Triangles(int *nQ, int **connections, int **face_lut)
{


  int
    i,
    new_nT = 2 * *nQ,
    *quads = *connections,
    *new_t = NULL,
    *t,
    *lut;

  new_t = (int *) DXAllocateZero(new_nT * 3 * sizeof (int));

  if (!new_t) goto error;

  *face_lut = (int *) DXAllocateZero(new_nT * sizeof (int));

  if (!(*face_lut)) goto error;


  t   = new_t;

  lut = *face_lut;

  for(i=0;i< *nQ;i++,quads+=4,lut+=2)
    {

      t[0] = quads[0];
      t[1] = quads[2];
      t[2] = quads[1];


      t+=3;


      t[0] = quads[1];
      t[1] = quads[2];
      t[2] = quads[3];

      t+=3;


      lut[0] = i;
      lut[1] = i;
    }


  *connections = new_t;


  *nQ = new_nT;

  return 1;

error:
  if (new_t)      DXFree((Pointer)new_t);
  if (*face_lut) {DXFree((Pointer)(*face_lut)); *face_lut = NULL;}
  return 0;
}
