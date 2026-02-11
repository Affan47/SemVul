e_pan_max_get(Evas_Object *obj, Evas_Coord *x, Evas_Coord *y)
{
   API_ENTRY return;
   if (x)
     {
        if (sd->w < sd->child_w) *x = sd->child_w - sd->w;
        else *x = 0;
     }
   if (y)
     {
        if (sd->h < sd->child_h) *y = sd->child_h - sd->h;
        else *y = 0;
     }
}
