data_write(void)
{
  double latsz,lonsz;
  maxlat = -9999.0;
  maxlon = -9999.0;
  minlat = 9999.0;
  minlon = 9999.0;
  rec_cnt = 0;

  short_length = atoi(snlen);
  mkshort_whandle = mkshort_new_handle();

  if (suppresswhite) {
    setshort_whitespace_ok(mkshort_whandle, 0);
  }

  setshort_length(mkshort_whandle, short_length);

  gbfprintf(file_out, "#tms-marker\n");
  waypt_disp_all(tiger_disp);

  if (genurl) {
    gbfile *urlf;

    urlf = gbfopen(genurl, "w", MYNAME);
    latsz = fabs(maxlat - minlat);
    lonsz = fabs(maxlon - minlon);


    gbfprintf(urlf, "lat=%f&lon=%f&ht=%f&wid=%f",
              minlat + (latsz/2.0),
              minlon + (lonsz/2.0),
              dscale(latsz),
              dscale(lonsz));

    gbfprintf(urlf, "&iwd=%s&iht=%s", xpixels, ypixels);
    gbfclose(urlf);
#if CLICKMAP
    if (clickmap) {
      linkf = gbfopen(clickmap, "w", MYNAME);
      gbfprintf(linkf, "<map name=\"map\">\n");
      waypt_disp_all(map_plot);
      gbfprintf(linkf, "</map>\n");
      gbfclose(linkf);
      linkf = NULL;
    }
#endif
  }

  mkshort_del_handle(&mkshort_whandle);
}
