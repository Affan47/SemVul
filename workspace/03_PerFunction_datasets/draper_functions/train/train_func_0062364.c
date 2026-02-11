get_contents_of_output(struct city_dialog *pdialog,
				   char *retbuf, int n)
{
  struct city *pcity;
  int goldtotal=0;
  int goldsurplus=0;
  int luxtotal=0;
  int scitotal=0;

  if (pdialog) {
    pcity=pdialog->pcity;
    goldtotal=pcity->prod[O_GOLD];
    goldsurplus = pcity->surplus[O_GOLD];
    luxtotal=pcity->prod[O_LUXURY];
    scitotal=pcity->prod[O_SCIENCE];
  }

  fc_snprintf(retbuf, n,
	  _("Gold:  %3d (%+-4d)\n"
	    "Lux:   %3d\n"
	    "Sci:   %3d"),
	  goldtotal, goldsurplus,
	  luxtotal,
	  scitotal);
}
