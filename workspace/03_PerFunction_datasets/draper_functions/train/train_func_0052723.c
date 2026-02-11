_dxfTransposePositions(Array array)
{

  int i, num;
  Point2D *scratch=NULL, *oldarrayptr;


  if (!DXGetArrayInfo(array, &num, NULL, NULL, NULL, NULL))
     goto error;
  oldarrayptr = (Point2D *)DXGetArrayData(array);
  scratch = (Point2D *)DXAllocate(num*sizeof(Point2D));
  if (!scratch) goto error;
  for (i=0; i<num; i+=2) {
     scratch[i/2]=oldarrayptr[i];
     scratch[num/2 + i/2 ]= oldarrayptr[i+1];
  }
  if (!DXAddArrayData(array, 0, num, scratch))
     goto error;

  DXFree(scratch);
  return OK;


error:
  DXFree(scratch);
  return ERROR;

}
