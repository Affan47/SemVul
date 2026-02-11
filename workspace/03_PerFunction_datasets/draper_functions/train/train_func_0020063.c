sph_normalize(HPoint3 *pt)
{


  float t = sqrt( pt->x*pt->x + pt->y*pt->y + pt->z*pt->z + pt->w*pt->w );
  if(t > 0) {
    pt->x /= t;
    pt->y /= t;
    pt->z /= t;
    pt->w /= t;
  }
}
