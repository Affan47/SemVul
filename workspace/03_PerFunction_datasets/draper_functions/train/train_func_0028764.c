ConvertPrimitiveToPath(const DrawInfo *ARGUNUSED(draw_info),
                       const PrimitiveInfo *primitive_info)
{
  PathInfo
    *path_info;

  PathInfoCode
    code;

  PointInfo
    p,
    q;

  register long
    i,
    n;

  long
    coordinates,
    start;


  switch (primitive_info->primitive)
  {
    case PointPrimitive:
    case ColorPrimitive:
    case MattePrimitive:
    case TextPrimitive:
    case ImagePrimitive:
      return((PathInfo *) NULL);
    default:
      break;
  }
  for (i=0; primitive_info[i].primitive != UndefinedPrimitive; i++);
  path_info=MagickAllocateArray(PathInfo *,(2*i+3),sizeof(PathInfo));
  if (path_info == (PathInfo *) NULL)
    return((PathInfo *) NULL);
  coordinates=0;
  n=0;
  p.x=(-1.0);
  p.y=(-1.0);
  q.x=(-1.0);
  q.y=(-1.0);
  start=0;
  for (i=0; primitive_info[i].primitive != UndefinedPrimitive; i++)
  {
    code=LineToCode;
    if (coordinates <= 0)
      {
        coordinates=(long) primitive_info[i].coordinates;
        p=primitive_info[i].point;
        start=n;
        code=MoveToCode;
      }
    coordinates--;


    if ((i == 0) || (fabs(q.x-primitive_info[i].point.x) > MagickEpsilon) ||
        (fabs(q.y-primitive_info[i].point.y) > MagickEpsilon))
      {
        path_info[n].code=code;
        path_info[n].point=primitive_info[i].point;
        q=primitive_info[i].point;
        n++;
      }
    if (coordinates > 0)
      continue;
    if ((fabs(p.x-primitive_info[i].point.x) <= MagickEpsilon) &&
        (fabs(p.y-primitive_info[i].point.y) <= MagickEpsilon))
      continue;


    path_info[start].code=OpenCode;
    path_info[n].code=GhostlineCode;
    path_info[n].point=primitive_info[i].point;
    n++;
    path_info[n].code=LineToCode;
    path_info[n].point=p;
    n++;
  }
  path_info[n].code=EndCode;
  path_info[n].point.x=0.0;
  path_info[n].point.y=0.0;
  if (IsEventLogging())
    LogPathInfo(path_info);
  return(path_info);
}
