reset_connection ()
{
  if (ictx && octx)
    {
      slog (L_INFO, _("%s(%s): connection lost"),
            conf->nodename, (const char *)si);

      if (::conf.script_node_down)
        {
          run_script_cb *cb = new run_script_cb;
          cb->set<connection, &connection::script_node_down> (this);
          run_script_queued (cb, _("node-down command execution failed, continuing."));
        }
    }

  delete ictx; ictx = 0;
  delete octx; octx = 0;

  si.host = 0;

  last_activity = 0.;

  retry_cnt = 0;

  rekey.stop ();
  keepalive.stop ();
  establish_connection.stop ();
}
