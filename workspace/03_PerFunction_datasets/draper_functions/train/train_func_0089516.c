_ibar_focus_launch(IBar *b)
{
   IBar_Icon *ic;
   Eina_List *l;

   if (!b->focused) return;
   EINA_LIST_FOREACH(b->icons, l, ic)
     {
        if (ic->focused)
          {
             _ibar_icon_go(ic, EINA_TRUE);
             break;
          }
     }
}
