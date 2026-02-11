engine_prep_camp_brief()
{
    gui_delete_message_pane(camp_pane);
    camp_pane = 0;
    engine_draw_bkgnd();

    camp_pane = gui_create_message_pane();

    {
        char *txt = alloca((camp_cur_scen->title ? strlen(camp_cur_scen->title) + 2 : 0)
                           + (last_debriefing ? strlen(last_debriefing) + 1 : 0)
                           + (camp_cur_scen->brief ? strlen(camp_cur_scen->brief) : 0) + 2 + 1);
        strcpy(txt, "");
        if (camp_cur_scen->title) {
            strcat(txt, camp_cur_scen->title);
            strcat(txt, "##");
        }
        if (last_debriefing) {
            strcat(txt, last_debriefing);
            strcat(txt, " ");
        }
        if (camp_cur_scen->brief) {
            strcat(txt, camp_cur_scen->brief);
            strcat(txt, "##");
        }
        gui_set_message_pane_text(camp_pane, txt);
    }


    if (camp_cur_scen->scen) {
      gui_set_message_pane_default(camp_pane, "nextscen");
    } else {
      List *ids = camp_get_result_list();
      List *vals = list_create(LIST_NO_AUTO_DELETE, LIST_NO_CALLBACK);
      char *result;

      list_reset(ids);
      while ((result = list_next(ids))) {
          const char *desc = camp_get_description(result);
          list_add(vals, desc ? (void *)desc : (void *)result);
      }


      if (ids->count == 0)
          gui_set_message_pane_default(camp_pane, " ");

      else if (ids->count == 1)
          gui_set_message_pane_default(camp_pane, list_first(ids));
      else
          gui_set_message_pane_options(camp_pane, ids, vals);

      list_delete(ids);
      list_delete(vals);
    }

    gui_draw_message_pane(camp_pane);
    engine_set_status(STATUS_CAMP_BRIEFING);
}
