g_date_determine_dmy(void)
{
GDate d;
gchar buf[128];
GDateParseTokens testpt;
gint i;

  DB( g_print("\n[dateentry] determine dmy\n") );


  g_date_clear (&d, 1);


      g_date_set_dmy (&d, 4, 7, 1976);

      g_date_strftime (buf, 127, "%x", &d);

      g_date_fill_parse_tokens (buf, &testpt);

      i = 0;
      while (i < testpt.num_ints)
        {
          switch (testpt.n[i])
            {
            case 7:
              dmy_order[i] = G_DATE_MONTH;
              break;
            case 4:
              dmy_order[i] = G_DATE_DAY;
              break;


            case 1976:
              dmy_order[2] = G_DATE_YEAR;
              break;
            }
          ++i;
        }

       DB( g_print(" dmy legend: 0=day, 1=month, 2=year\n") );
       DB( g_print(" dmy is: %d %d %d\n", dmy_order[0], dmy_order[1], dmy_order[2]) );
}
