convert_eols(char *in_buffer,int in_size,char *out_buffer,int *out_size,int *in_state) {
  int in_pos,out_pos;
  int status;
  char in_char;

  out_pos=0;
  status=*in_state;

  if (status==100 || status==101) {
    if (status==101) {
      out_buffer[out_pos++]='\r';
      out_buffer[out_pos++]='\n';
    }
  } else {
    for (in_pos=0;in_pos<in_size;in_pos++) {
      in_char=in_buffer[in_pos];

      switch (status) {
        case 0:
          if (in_char=='\r') status=1;
          if (in_char=='\n') {
            out_buffer[out_pos++]='\r';
            out_buffer[out_pos++]='\n';
          }
          if ((in_char!='\r') && (in_char!='\n')) out_buffer[out_pos++]=in_char;
        break;

        case 1:
          out_buffer[out_pos++]='\r';
          out_buffer[out_pos++]='\n';

          if (in_char!='\n') out_buffer[out_pos++]=in_char;

          status=0;
        break;
      }
    }
  }

  *out_size=out_pos;
  *in_state=status;
}
