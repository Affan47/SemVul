cbf_reset_refcounts( cbf_handle dictionary ) {

  if ( dictionary && !cbf_find_tag(dictionary,"_items.name"))  {

    cbf_failnez(cbf_reset_column(dictionary, "CBF_wide_refcounts") )

    cbf_failnez(cbf_reset_column(dictionary, "DB_wide_refcounts") )

    cbf_failnez(cbf_reset_column(dictionary, "DBcat_wide_refcounts") )

    cbf_failnez(cbf_reset_column(dictionary, "SF_wide_refcounts") )

    cbf_failnez(cbf_reset_column(dictionary, "SFcat_wide_refcounts") )
  }

  return 0;

}
