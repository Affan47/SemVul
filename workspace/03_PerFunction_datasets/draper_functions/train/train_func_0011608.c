getmy(elem,wininfo)
znc	*elem;
WinZnc	*wininfo;
{
  long x1,y1,ny1;
  long ix1,ix2,iy1,iy2;

  y1=(elem->y1-wininfo->my)/wininfo->PY;
  x1=(elem->x1-wininfo->mx)/wininfo->PX;
  ny1=y1;
  if(y1>=1)
  {
    ix1=x1*wininfo->PX+wininfo->mx;
    iy1=(y1-1)*wininfo->PY+wininfo->my;
    ix2=ix1+wininfo->PX;
    iy2=iy1+wininfo->PY;


    if( elem->x1<=ix2 && ix1<=elem->x2 && iy1<=elem->y2 && elem->y1<=iy2 )
      ny1=y1-1;
  }
  y1=ny1;
  return(ny1);
}
