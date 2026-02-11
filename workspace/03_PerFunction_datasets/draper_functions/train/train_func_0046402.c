_e_toolbar_orient_string_get(E_Toolbar *tbar)
{
   const char *sig = "";

   switch (tbar->gadcon->orient)
     {
      case E_GADCON_ORIENT_HORIZ:
        sig = "horizontal";
        break;

      case E_GADCON_ORIENT_VERT:
        sig = "vertical";
        break;

      case E_GADCON_ORIENT_LEFT:
        sig = "left";
        break;

      case E_GADCON_ORIENT_RIGHT:
        sig = "right";
        break;

      case E_GADCON_ORIENT_TOP:
        sig = "top";
        break;

      case E_GADCON_ORIENT_BOTTOM:
        sig = "bottom";
        break;

      default:
        break;
     }
   return sig;
}
