check_collision (RTPSession * sess, RTPSource * source,
    RTPArrivalStats * arrival, gboolean rtp)
{

  if (!arrival->have_address)
    return FALSE;

  if (sess->source != source) {
    GstNetAddress *from;
    gboolean have_from;


    if (rtp) {
      from = &source->rtp_from;
      have_from = source->have_rtp_from;
    } else {
      from = &source->rtcp_from;
      have_from = source->have_rtcp_from;
    }

    if (have_from) {
      if (gst_netaddress_equal (from, &arrival->address)) {

        return FALSE;
      } else {
        GST_LOG ("we have a third-party collision or loop ssrc:%x",
            rtp_source_get_ssrc (source));
        if (sess->favor_new) {
          if (rtp_source_find_conflicting_address (source,
                  &arrival->address, arrival->current_time)) {
            gchar buf1[40];
            gst_netaddress_to_string (&arrival->address, buf1, 40);
            GST_LOG ("Known conflict on %x for %s, dropping packet",
                rtp_source_get_ssrc (source), buf1);
            return TRUE;
          } else {
            gchar buf1[40], buf2[40];


            rtp_source_add_conflicting_address (source, from,
                arrival->current_time);

            gst_netaddress_to_string (from, buf1, 40);
            gst_netaddress_to_string (&arrival->address, buf2, 40);
            GST_DEBUG ("New conflict for ssrc %x, replacing %s with %s,"
                " saving old as known conflict",
                rtp_source_get_ssrc (source), buf1, buf2);

            if (rtp)
              rtp_source_set_rtp_from (source, &arrival->address);
            else
              rtp_source_set_rtcp_from (source, &arrival->address);
            return FALSE;
          }
        } else {

          return TRUE;
        }
      }
    } else {

      if (rtp)
        rtp_source_set_rtp_from (source, &arrival->address);
      else
        rtp_source_set_rtcp_from (source, &arrival->address);
      return FALSE;
    }


    if (arrival->current_time > source->last_activity) {
      GstClockTime inactivity_period =
          arrival->current_time - source->last_activity;
      if (inactivity_period > 1 * GST_SECOND) {

        if (rtp) {
          g_assert (source->have_rtp_from);
          rtp_source_set_rtp_from (source, &arrival->address);
        } else {
          g_assert (source->have_rtcp_from);
          rtp_source_set_rtcp_from (source, &arrival->address);
        }
        return FALSE;
      }
    }
  } else {


    if (rtp_source_find_conflicting_address (source, &arrival->address,
            arrival->current_time)) {


      GST_DEBUG ("Our packets are being looped back to us, dropping");
    } else {


      rtp_source_add_conflicting_address (source, &arrival->address,
          arrival->current_time);

      GST_DEBUG ("Collision for SSRC %x", rtp_source_get_ssrc (source));
      on_ssrc_collision (sess, source);

      rtp_session_schedule_bye_locked (sess, "SSRC Collision",
          arrival->current_time);

      sess->change_ssrc = TRUE;
    }
  }

  return TRUE;
}
