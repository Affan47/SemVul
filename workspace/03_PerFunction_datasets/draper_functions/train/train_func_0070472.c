_ecore_evas_x_group_leader_set(Ecore_Evas *ee)
{
   leader_ref++;
   if (leader_ref == 1)
     {
        char *id = NULL;

        leader_win =
          ecore_x_window_override_new(ee->engine.x.win_root, 1234, 5678, 1, 2);
        ecore_x_window_defaults_set(leader_win);
        if ((id = getenv("DESKTOP_STARTUP_ID")))
          ecore_x_netwm_startup_id_set(leader_win,id);
        ecore_x_icccm_client_leader_set(leader_win, leader_win);
     }
   ee->engine.x.leader = leader_win;
   ecore_x_icccm_client_leader_set(ee->prop.window, leader_win);
}
