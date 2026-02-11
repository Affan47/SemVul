iter_resize(ip,new_lenb,new_lenx)
ITER *ip;
int new_lenb, new_lenx;
{
   VEC *old;

   if ( ip == (ITER *) NULL)
     error(E_NULL,"iter_resize");

   old = ip->x;
   ip->x = v_resize(ip->x,new_lenx);
   if ( ip->shared_x && old != ip->x )
     warning(WARN_SHARED_VEC,"iter_resize");
   old = ip->b;
   ip->b = v_resize(ip->b,new_lenb);
   if ( ip->shared_b && old != ip->b )
     warning(WARN_SHARED_VEC,"iter_resize");

   return ip;
}
