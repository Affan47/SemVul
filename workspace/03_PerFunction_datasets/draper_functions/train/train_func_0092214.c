_ecore_evas_extn_cb_hide(void *data, Evas *e __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Ecore_Evas *ee;
   Extn *extn;

   ee = data;
   ee->visible = 0;
   extn = ee->engine.buffer.data;
   if (!extn) return;
   if (!extn->ipc.server) return;
   ecore_ipc_server_send(extn->ipc.server, MAJOR, OP_HIDE, 0, 0, 0, NULL, 0);
}
