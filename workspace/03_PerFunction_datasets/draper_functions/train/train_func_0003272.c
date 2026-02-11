xsh_utils_compute_airm(cpl_frameset* raws)
{

  cpl_frame* frm=NULL;
  cpl_propertylist* plist=NULL;
  const char* name=NULL;
  int i=0;
  int size=0;
  double airm=0;
  double airm_eff=0;
  double exptime=0;
  double time_tot=0;
  double* pairm=NULL;
  double* pprod=NULL;
  double* ptime=NULL;

  cpl_array* time_array=NULL;
  cpl_array* airm_array=NULL;


  XSH_ASSURE_NOT_NULL_MSG(raws,"raws frameset null pointer");

  size=cpl_frameset_get_size(raws);
  airm_array=cpl_array_new(size,CPL_TYPE_DOUBLE);
  time_array=cpl_array_new(size,CPL_TYPE_DOUBLE);

  pairm=cpl_array_get_data_double(airm_array);
  ptime=cpl_array_get_data_double(time_array);
  pprod=cpl_array_get_data_double(time_array);

  if(size>2) {
    for(i=0;i<size;i++){

      frm=cpl_frameset_get_frame(raws,i);
      name=cpl_frame_get_filename(frm);
      plist=cpl_propertylist_load(name,0);
      airm=xsh_pfits_get_airm_mean(plist);
      exptime=xsh_pfits_get_exptime(plist);
      ptime[i]=exptime;
      pairm[i]=airm;
      pprod[i]=airm*exptime;

    }
    airm_eff=(pprod[0]+pprod[size-1])/(ptime[0]+ptime[size-1]);

  } else if (size == 2) {
    frm=cpl_frameset_get_frame(raws,0);
    name=cpl_frame_get_filename(frm);
    plist=cpl_propertylist_load(name,0);

    airm=xsh_pfits_get_airm_mean(plist);
    exptime=xsh_pfits_get_exptime(plist);

    airm_eff=airm*exptime;
    time_tot=exptime;

    frm=cpl_frameset_get_frame(raws,1);
    name=cpl_frame_get_filename(frm);
    plist=cpl_propertylist_load(name,0);


    airm_eff+=airm*exptime;
    time_tot+=exptime;

    airm_eff/=time_tot;
  } else {

    frm=cpl_frameset_get_frame(raws,0);
    name=cpl_frame_get_filename(frm);
    plist=cpl_propertylist_load(name,0);

    airm=xsh_pfits_get_airm_mean(plist);
    exptime=xsh_pfits_get_exptime(plist);

    airm_eff=airm;
  }

  cleanup:
  return airm_eff;

}
