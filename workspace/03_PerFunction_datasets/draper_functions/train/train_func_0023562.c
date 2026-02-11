e_gadcon_orient(E_Gadcon *gc, E_Gadcon_Orient orient)
{
   Eina_List *l;
   E_Gadcon_Client *gcc;
   int horiz = 0;

   E_OBJECT_CHECK(gc);
   E_OBJECT_IF_NOT_TYPE(gc, E_GADCON_DUMMY_TYPE)
     E_OBJECT_TYPE_CHECK(gc, E_GADCON_TYPE);
   if (gc->orient == orient) return;
   gc->orient = orient;
   if (gc->dummy) return;
   e_gadcon_layout_freeze(gc->o_container);
   switch (gc->orient)
     {
      case E_GADCON_ORIENT_FLOAT:
      case E_GADCON_ORIENT_HORIZ:
      case E_GADCON_ORIENT_TOP:
      case E_GADCON_ORIENT_BOTTOM:
      case E_GADCON_ORIENT_CORNER_TL:
      case E_GADCON_ORIENT_CORNER_TR:
      case E_GADCON_ORIENT_CORNER_BL:
      case E_GADCON_ORIENT_CORNER_BR:
        horiz = 1;
        break;

      case E_GADCON_ORIENT_VERT:
      case E_GADCON_ORIENT_LEFT:
      case E_GADCON_ORIENT_RIGHT:
      case E_GADCON_ORIENT_CORNER_LT:
      case E_GADCON_ORIENT_CORNER_RT:
      case E_GADCON_ORIENT_CORNER_LB:
      case E_GADCON_ORIENT_CORNER_RB:
        horiz = 0;
        break;

      default:
        break;
     }
   e_gadcon_layout_orientation_set(gc->o_container, horiz);
   EINA_LIST_FOREACH(gc->clients, l, gcc)
     {
        e_box_orientation_set(gcc->o_box, horiz);
        if (gcc->client_class->func.orient)
          gcc->client_class->func.orient(gcc, gc->orient);
     }
   e_gadcon_layout_thaw(gc->o_container);
}
