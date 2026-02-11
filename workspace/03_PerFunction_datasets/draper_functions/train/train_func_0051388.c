_e_container_shape_change_call(E_Container_Shape *es, E_Container_Shape_Change ch)
{
   Eina_List *l = NULL;
   E_Container_Shape_Callback *cb = NULL;

   if ((!es) || (!es->con) || (!es->con->shape_change_cb)) return;
   EINA_LIST_FOREACH(es->con->shape_change_cb, l, cb)
     {
        if (!cb) continue;
        cb->func(cb->data, es, ch);
     }
}
