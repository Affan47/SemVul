init_user (struct scanner *s)
{

  DBG (10, "init_user: start\n");


  if(s->has_flatbed)
    s->u.source = SOURCE_FLATBED;
  else if(s->has_adf)
    s->u.source = SOURCE_ADF_FRONT;
  else if(s->has_card)
    s->u.source = SOURCE_CARD_FRONT;


  if(s->can_monochrome)
    s->u.mode=MODE_LINEART;
  else if(s->can_halftone)
    s->u.mode=MODE_HALFTONE;
  else if(s->can_grayscale)
    s->u.mode=MODE_GRAYSCALE;
  else if(s->can_color)
    s->u.mode=MODE_COLOR;


  s->u.dpi_x = s->basic_x_res;
  s->u.dpi_y = s->basic_x_res;


  s->u.page_x = 8.5 * 1200;
  if(s->u.page_x > s->valid_x){
    s->u.page_x = s->valid_x;
  }


  s->u.page_y = 11 * 1200;
  if(s->u.page_y > s->max_y){
    s->u.page_y = s->max_y;
  }


  s->u.br_x = s->u.page_x;


  s->u.br_y = s->u.page_y;

  s->threshold = 90;
  s->compress_arg = 50;

  DBG (10, "init_user: finish\n");

  return SANE_STATUS_GOOD;
}
