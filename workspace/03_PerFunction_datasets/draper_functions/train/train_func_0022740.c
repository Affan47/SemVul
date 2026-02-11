must_fully_buffer(struct fujitsu *s)
{
  if(s->hwdeskewcrop){
    return 1;
  }

  if(
    (s->swdeskew || s->swdespeck || s->swcrop || s->swskip)
#ifdef SANE_FRAME_JPEG
    && s->s_params.format != SANE_FRAME_JPEG
#endif
  ){
    return 1;
  }

  return 0;
}
