parse_obsolete_tdat_frame (ID3TagsWorking * work)
{
  if (work->parse_size >= 5 &&
      work->parse_data[0] == ID3V2_ENCODING_ISO8859 &&
      g_ascii_isdigit (work->parse_data[1]) &&
      g_ascii_isdigit (work->parse_data[2]) &&
      g_ascii_isdigit (work->parse_data[3]) &&
      g_ascii_isdigit (work->parse_data[4])) {

    guint pending_day = (10 * g_ascii_digit_value (work->parse_data[1])) +
        g_ascii_digit_value (work->parse_data[2]);
    guint pending_month = (10 * g_ascii_digit_value (work->parse_data[3])) +
        g_ascii_digit_value (work->parse_data[4]);

    if (pending_day >= 1 && pending_day <= 31 && pending_month >= 1
        && pending_month <= 12) {
      GST_LOG ("date (dd/mm) %02u/%02u", pending_day, pending_month);
      work->pending_day = pending_day;
      work->pending_month = pending_month;
    } else {
      GST_WARNING ("Ignoring invalid ID3v2 TDAT frame (dd/mm) %02u/%02u",
          pending_day, pending_month);
    }
  }
}
