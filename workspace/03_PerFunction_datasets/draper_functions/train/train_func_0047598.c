twoDdisplay()
{
  gc_sound_play_ogg ("sounds/flip.wav", NULL);
  gc_set_default_background(goo_canvas_get_root_item(gcomprisBoard->canvas));

  if (threedgroup)
    g_object_set (threedgroup, "visibility", GOO_CANVAS_ITEM_INVISIBLE, NULL);
  g_object_set (boardRootItem, "visibility", GOO_CANVAS_ITEM_VISIBLE, NULL);
  threeDactive=FALSE;
}
