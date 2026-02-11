gl_find_char(GetLine *gl, int count, int forward, int onto, char c)
{
  int pos;
  int i;


  if(!c) {


    if(gl->vi.repeat.active) {
      c = gl->vi.find_char;
    } else {
      if(gl_read_terminal(gl, 1, &c))
	return -1;


      gl->vi.find_forward = forward;
      gl->vi.find_onto = onto;
      gl->vi.find_char = c;
    };
  };


  if(forward) {


    for(i=0, pos=gl->buff_curpos; i<count && pos < gl->ntotal; i++) {


      pos++;


      for( ; pos<gl->ntotal && c!=gl->line[pos]; pos++)
	;
    };


    if(!onto && pos<gl->ntotal)
      pos--;
  } else {


    for(i=0, pos=gl->buff_curpos; i<count && pos >= gl->insert_curpos; i++) {


      pos--;


      for( ; pos>=gl->insert_curpos && c!=gl->line[pos]; pos--)
	;
    };


    if(!onto && pos>=gl->insert_curpos)
      pos++;
  };


  if(pos >= gl->insert_curpos && pos < gl->ntotal) {
    return pos;
  } else {
    (void) gl_ring_bell(gl, 1, NULL);
    return -1;
  }
}
