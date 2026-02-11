e_scrollframe_child_region_show(Evas_Object *obj, Evas_Coord x, Evas_Coord y, Evas_Coord w, Evas_Coord h)
{
   Evas_Coord mx = 0, my = 0, cw = 0, ch = 0, px = 0, py = 0, nx, ny, vw, vh;

   API_ENTRY return;
   if (!sd->pan_obj) return;
   sd->pan_func.max_get(sd->pan_obj, &mx, &my);
   sd->pan_func.child_size_get(sd->pan_obj, &cw, &ch);
   sd->pan_func.get(sd->pan_obj, &px, &py);
   e_scrollframe_child_viewport_size_get(obj, &vw, &vh);


   if ((px <= x) && (py <= y) && (x + w <= px + vw) && (y + h <= py + vh))
      return;

   nx = px;
   if (x < px) nx = x;
   else if ((x + w) > (px + (cw - mx)))
     {
        nx = x + w - (cw - mx);
        if (nx > x) nx = x;
     }
   ny = py;
   if (y < py) ny = y;
   else if ((y + h) > (py + (ch - my)))
     {
        ny = y + h - (ch - my);
        if (ny > y) ny = y;
     }
   if ((nx == px) && (ny == py)) return;
   e_scrollframe_child_pos_set(obj, nx, ny);
}
