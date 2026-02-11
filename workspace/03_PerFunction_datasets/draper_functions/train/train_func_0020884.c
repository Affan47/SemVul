tls_handshake_timeout_cb(gpointer data)
{


  World *world = (World *) data;


  if (g_list_index(open_worlds, world) != -1 && world->connecting) {
    gnutls_deinit(world->tls_session);
    world->errmsg = g_strdup_printf(_("SSL Handshake took too long."));
    disconnect_world(world, FALSE);
  }


  return FALSE;
}
