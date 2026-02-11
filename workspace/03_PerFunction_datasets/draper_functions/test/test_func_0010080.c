eina_quadtree_resize(Eina_QuadTree *q, size_t w, size_t h)
{
   EINA_MAGIC_CHECK_QUADTREE(q);

   if (q->geom.w == w
       && q->geom.h == h)
      return;

   q->resize = EINA_TRUE;
   q->geom.w = w;
   q->geom.h = h;
}
