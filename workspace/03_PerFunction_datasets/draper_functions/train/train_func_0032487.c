e_layout_coord_canvas_to_virtual(Evas_Object *obj, Evas_Coord cx, Evas_Coord cy, Evas_Coord *vx, Evas_Coord *vy)
{
   E_Smart_Data *sd;

   if (evas_object_smart_smart_get(obj) != _e_smart) SMARTERRNR();
   sd = evas_object_smart_data_get(obj);

   if (vx) *vx = (cx - sd->x) * ((double)(sd->vw) / sd->w);
   if (vy) *vy = (cy - sd->y) * ((double)(sd->vh) / sd->h);
}
