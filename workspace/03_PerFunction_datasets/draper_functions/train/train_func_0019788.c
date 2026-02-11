p_set_layout_preset(GapStbMainGlobalParams *sgpp)
{
  GapStbTabWidgets *tabw;

  if(sgpp)
  {
    tabw = sgpp->stb_widgets;
    if(tabw)
    {
      tabw->cols = sgpp->stb_cols;
      tabw->rows = sgpp->stb_rows;
      tabw->thumbsize = sgpp->stb_thumbsize;
      tabw->edmode = GAP_STB_EDMO_FRAME_NUMBER;
      if(tabw->thumbsize <= STB_THSIZE_SMALL)
      {


        tabw->edmode = GAP_STB_EDMO_SEQUENCE_NUMBER;
      }
    }

    tabw = sgpp->cll_widgets;
    if(tabw)
    {
      tabw->cols = sgpp->cll_cols;
      tabw->rows = sgpp->cll_rows;
      tabw->thumbsize = sgpp->cll_thumbsize;
      tabw->edmode = GAP_STB_EDMO_SEQUENCE_NUMBER;
    }
  }
}
