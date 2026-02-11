glh_step_stream(GlhLineStream *str)
{


  str->c = str->seg ? str->seg->s[str->posn] : '\0';


  if(str->c != '\0' && ++str->posn >= GLH_SEG_SIZE) {
    str->posn = 0;
    str->seg = str->seg->next;
  };
}
