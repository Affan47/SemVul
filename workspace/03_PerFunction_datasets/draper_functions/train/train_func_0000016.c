rep_hist_record_mtbf_data(time_t now, int missing_means_down)
{
  char time_buf[ISO_TIME_LEN+1];

  digestmap_iter_t *orhist_it;
  const char *digest;
  void *or_history_p;
  or_history_t *hist;
  open_file_t *open_file = NULL;
  FILE *f;

  {
    char *filename = get_datadir_fname("router-stability");
    f = start_writing_to_stdio_file(filename, OPEN_FLAGS_REPLACE|O_TEXT, 0600,
                                    &open_file);
    tor_free(filename);
    if (!f)
      return -1;
  }


#define PUT(s) STMT_BEGIN if (fputs((s),f)<0) goto err; STMT_END
#define PRINTF(args) STMT_BEGIN if (fprintf args <0) goto err; STMT_END

  PUT("format 2\n");

  format_iso_time(time_buf, time(NULL));
  PRINTF((f, "stored-at %s\n", time_buf));

  if (started_tracking_stability) {
    format_iso_time(time_buf, started_tracking_stability);
    PRINTF((f, "tracked-since %s\n", time_buf));
  }
  if (stability_last_downrated) {
    format_iso_time(time_buf, stability_last_downrated);
    PRINTF((f, "last-downrated %s\n", time_buf));
  }

  PUT("data\n");


  for (orhist_it = digestmap_iter_init(history_map);
       !digestmap_iter_done(orhist_it);
       orhist_it = digestmap_iter_next(history_map,orhist_it)) {
    char dbuf[HEX_DIGEST_LEN+1];
    const char *t = NULL;
    digestmap_iter_get(orhist_it, &digest, &or_history_p);
    hist = (or_history_t*) or_history_p;

    base16_encode(dbuf, sizeof(dbuf), digest, DIGEST_LEN);

    if (missing_means_down && hist->start_of_run &&
        !router_get_by_id_digest(digest)) {


      log_info(LD_HIST,
               "Relay '%s' is listed as up in rephist, but it's not in "
               "our routerlist. Correcting.", dbuf);
      rep_hist_note_router_unreachable(digest, now);
    }

    PRINTF((f, "R %s\n", dbuf));
    if (hist->start_of_run > 0) {
      format_iso_time(time_buf, hist->start_of_run);
      t = time_buf;
    }
    PRINTF((f, "+MTBF %lu %.5lf%s%s\n",
            hist->weighted_run_length, hist->total_run_weights,
            t ? " S=" : "", t ? t : ""));
    t = NULL;
    if (hist->start_of_downtime > 0) {
      format_iso_time(time_buf, hist->start_of_downtime);
      t = time_buf;
    }
    PRINTF((f, "+WFU %lu %lu%s%s\n",
            hist->weighted_uptime, hist->total_weighted_time,
            t ? " S=" : "", t ? t : ""));
  }

  PUT(".\n");

#undef PUT
#undef PRINTF

  return finish_writing_to_file(open_file);
 err:
  abort_writing_to_file(open_file);
  return -1;
}
