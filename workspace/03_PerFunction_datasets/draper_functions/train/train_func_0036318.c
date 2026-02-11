evas_map_util_3d_perspective(Evas_Map *m,
                             Evas_Coord px, Evas_Coord py,
                             Evas_Coord z0, Evas_Coord foc)
{
   MAGIC_CHECK(m, Evas_Map, MAGIC_MAP);
   return;
   MAGIC_CHECK_END();

   Evas_Map_Point *p, *p_end;

   p = m->points;
   p_end = p + m->count;

   m->persp.px = px;
   m->persp.py = py;
   m->persp.z0 = z0;
   m->persp.foc = foc;

   if (foc <= 0) return;

   for (; p < p_end; p++)
     {
        double x, y, zz;

        x = p->x - px;
        y = p->y - py;

        zz = ((p->z - z0) + foc);

        if (zz > 0)
          {
             x = (x * foc) / zz;
             y = (y * foc) / zz;
          }

        p->x = px + x;
        p->y = py + y;
     }
}
