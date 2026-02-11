evt_start_event (sc_gameref_t game, sc_int event)
{
  const sc_filterref_t filter = gs_get_filter (game);
  const sc_prop_setref_t bundle = gs_get_bundle (game);
  sc_vartype_t vt_key[4];
  sc_int time1, time2, obj1, obj1dest;

  if (evt_trace)
    sc_trace ("Event: starting event %ld\n", event);


  if (evt_can_see_event (game, event))
    {
      const sc_char *starttext;


      vt_key[0].string = "Events";
      vt_key[1].integer = event;
      vt_key[2].string = "StartText";
      starttext = prop_get_string (bundle, "S<-sis", vt_key);
      if (!sc_strempty (starttext))
        {
          pf_buffer_string (filter, starttext);
          pf_buffer_character (filter, '\n');
        }


      vt_key[2].string = "Res";
      vt_key[3].integer = 0;
      res_handle_resource (game, "sisi", vt_key);
    }


  vt_key[0].string = "Events";
  vt_key[1].integer = event;
  vt_key[2].string = "Obj1";
  obj1 = prop_get_integer (bundle, "I<-sis", vt_key) - 1;
  vt_key[2].string = "Obj1Dest";
  obj1dest = prop_get_integer (bundle, "I<-sis", vt_key) - 1;
  evt_move_object (game, obj1, obj1dest);


  gs_set_event_state (game, event, ES_RUNNING);

  vt_key[2].string = "Time1";
  time1 = prop_get_integer (bundle, "I<-sis", vt_key);
  vt_key[2].string = "Time2";
  time2 = prop_get_integer (bundle, "I<-sis", vt_key);
  gs_set_event_time (game, event, sc_randomint (time1, time2));

  if (evt_trace)
    sc_trace ("Event: start event handling done, %ld\n", event);
}
