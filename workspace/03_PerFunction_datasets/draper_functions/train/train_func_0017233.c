mgribwindow(WnWindow *win)
{
  WnPosition wp;
  int xsize, ysize;
  char fullscene[280], fullcreator[280], fullfor[280], fulldate[280];
  char dpyname[PATH_MAX];


  sprintf(fullscene,"Scene %s",_mgribc->ribscene);
  sprintf(fullcreator,"Creator %s",_mgribc->ribcreator);
  sprintf(fullfor,"For %s",_mgribc->ribfor);
  sprintf(fulldate,"CreationDate %s",_mgribc->ribdate);
  mrti(mr_header,"RenderMan RIB-Structure 1.0", mr_nl,
       mr_header, fullscene, mr_nl,
       mr_header, fullcreator, mr_nl,
       mr_header, fulldate, mr_nl,
       mr_header, fullfor, mr_nl,
       mr_header, "Frames 1", mr_nl,
       mr_NULL);


  if(_mgribc->shader != RM_STDSHADE && _mgribc->shadepath) {
    mrti(mr_header, "CapabilitiesNeeded ShadingLanguage", mr_nl,
	 mr_embed, "version 3.03", mr_nl,
	 mr_option, mr_string, "searchpath", mr_string, "shader",
	 mr_nl, mr_embed, "[", mr_string, _mgribc->shadepath,
	 mr_embed, "]", mr_nl, mr_nl, mr_NULL);
  } else {
    mrti(mr_embed, "version 3.03", mr_nl, mr_nl, mr_NULL);
  }


  snprintf(dpyname, PATH_MAX, "%s%s", _mgribc->displaybase,
	   _mgribc->display == MG_RIBTIFF ? ".tiff" : ".rib");
  mrti(mr_display, mr_string, dpyname,
       (_mgribc->display == MG_RIBFRAME) ? mr_framebuffer : mr_file,
       (_mgribc->backing == MG_RIBDOBG) ? mr_rgb : mr_rgba, mr_NULL);


  WnGet(_mgc->win, WN_CURPOS, &wp);
  xsize = wp.xmax - wp.xmin + 1;
  ysize = wp.ymax - wp.ymin + 1;
  mrti(mr_format, mr_int, xsize, mr_int, ysize, mr_float, 1., mr_NULL);

  _mgribc->born = true;
  return win;
}
