check_status(adns_status st) {
  static const adns_status statuspoints[]= {
    adns_s_ok,
    adns_s_max_localfail, adns_s_max_remotefail, adns_s_max_tempfail,
    adns_s_max_misconfig, adns_s_max_misquery
  };

  const adns_status *spp;
  int minrcode;

  for (minrcode=0, spp=statuspoints;
       spp < statuspoints + (sizeof(statuspoints)/sizeof(statuspoints[0]));
       spp++)
    if (st > *spp) minrcode++;
  if (rcode < minrcode) rcode= minrcode;
}
