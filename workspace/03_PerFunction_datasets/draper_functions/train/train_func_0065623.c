sinfo_rec_mflat(cpl_parameterlist *config, cpl_frameset *set)
{

  cpl_parameter* p;
  cpl_frameset* ref_set=NULL;
  int pdensity=0;
  int line_cor=0;

  check_nomsg(p=cpl_parameterlist_find(config,"sinfoni.product.density"));
  check_nomsg(pdensity=cpl_parameter_get_int(p));

  sinfo_msg("Welcome to SINFONI Pipeline release %d.%d.%d",
        SINFONI_MAJOR_VERSION,SINFONI_MINOR_VERSION,SINFONI_MICRO_VERSION);
  ck0(sinfo_dfs_set_groups(set),"Cannot indentify RAW and CALIB frames") ;

  check_nomsg(p=cpl_parameterlist_find(config, "sinfoni.general.lc_sw"));
  check_nomsg(line_cor=cpl_parameter_get_bool(p));
  if(line_cor==1) {
     check_nomsg(sinfo_ima_line_cor(config,set));
  }


  check_nomsg(ref_set=cpl_frameset_duplicate(set));
  sinfo_bp_config_add(config);
  check_nomsg(p = cpl_parameterlist_find(config,"sinfoni.bp.method"));
  check_nomsg(cpl_parameter_set_string(p,"Normal"));


  sinfo_msg("-------------------------------------------");
  sinfo_msg("MASTER FLAT DETERMINATION                  ");
  sinfo_msg("-------------------------------------------");

  ck0(sinfo_new_lamp_flats(cpl_func,config,set,ref_set),
      "MASTER FLAT DETERMINATION FAILED");
  sinfo_msg("MASTER FLAT DETERMINATION SUCCESS") ;

  sinfo_msg("-------------------------------------------");
  sinfo_msg("BP_MAP_NO BAD PIXEL MAP DETERMINATION      ");
  sinfo_msg("-------------------------------------------");


  check_nomsg(p = cpl_parameterlist_find(config,"sinfoni.bp.method"));
  check_nomsg(cpl_parameter_set_string(p,"Normal"));
  ck0(sinfo_new_bp_search_normal(cpl_func,config,set,ref_set,PRO_BP_MAP_NO),
  "BP_MAP_NO BAD PIXEL MAP DETERMINATION FAILED") ;

  sinfo_msg("------------------------------------------");
  sinfo_msg("MASTER_BP_MAP BAD PIXEL MAP DETERMINATION ");
  sinfo_msg("------------------------------------------");
  ck0(sinfo_new_add_bp_map(cpl_func,config, set,ref_set),
     "MASTER_BP_MAP BAD PIXEL MAP FAILED") ;
  sinfo_msg("MASTER_BP_MAP BAD PIXEL MAP DETERMINATION SUCCESS");


  if(pdensity < 2) {
     check_nomsg(cpl_frameset_erase(set,PRO_BP_MAP_NO));
  }

 cleanup:

  sinfo_free_frameset(&ref_set);

  if (cpl_error_get_code() != CPL_ERROR_NONE) {
    return -1;
  } else {
    return 0;
  }

}
