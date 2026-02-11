pipe_region_expand(Evas_Engine_GL_Context *gc, int n,
                   int x, int y, int w, int h)
{
   int x1, y1, x2, y2;

   if (gc->pipe[n].region.w <= 0)
     {
        gc->pipe[n].region.x = x;
        gc->pipe[n].region.y = y;
        gc->pipe[n].region.w = w;
        gc->pipe[n].region.h = h;
        return;
     }
   x1 = gc->pipe[n].region.x;
   y1 = gc->pipe[n].region.y;
   x2 = gc->pipe[n].region.x + gc->pipe[n].region.w;
   y2 = gc->pipe[n].region.y + gc->pipe[n].region.h;
   if (x < x1) x1 = x;
   if (y < y1) y1 = y;
   if ((x + w) > x2) x2 = x + w;
   if ((y + h) > y2) y2 = y + h;
   gc->pipe[n].region.x = x1;
   gc->pipe[n].region.y = y1;
   gc->pipe[n].region.w = x2 - x1;
   gc->pipe[n].region.h = y2 - y1;
}
