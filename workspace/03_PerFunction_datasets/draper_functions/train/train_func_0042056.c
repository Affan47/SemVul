_e_mod_quickpanel_animate_down(E_Illume_Quickpanel *qp)
{
   Eina_List *l;
   E_Border *bd;
   int pbh = 0;

   if (!qp) return;
   pbh = (qp->vert.isize - qp->vert.size);
   EINA_LIST_FOREACH(qp->borders, l, bd)
     {

        if (e_object_is_del(E_OBJECT(bd))) continue;
        if (bd->fx.y != (qp->vert.adjust + pbh))
          e_border_fx_offset(bd, 0, (qp->vert.adjust + pbh));
        pbh += bd->h;

        if (!qp->visible)
          {
             if (bd->fx.y > 0)
               {
                  if (!bd->visible) e_illume_border_show(bd);
               }
          }
        else
          {
             if (bd->fx.y <= 10)
               {
                  if (bd->visible) e_illume_border_hide(bd);
               }
          }
     }
}
