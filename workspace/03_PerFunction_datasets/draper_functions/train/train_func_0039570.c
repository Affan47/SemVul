_e_border_under_pointer_helper(E_Desk *desk, E_Border *exclude, int x, int y)
{
   E_Border *bd = NULL, *cbd;
   Eina_List *l;

   EINA_LIST_FOREACH(e_border_raise_stack_get(), l, cbd)
     {
        if (!cbd) continue;


        if ((exclude) && (cbd == exclude)) continue;
        if ((desk) && (cbd->desk != desk)) continue;
        if (!E_INSIDE(x, y, cbd->x, cbd->y, cbd->w, cbd->h))
          continue;


        if (!bd || (cbd->layer > bd->layer))
          {
             bd = cbd;
             break;
          }
     }
   return bd;
}
