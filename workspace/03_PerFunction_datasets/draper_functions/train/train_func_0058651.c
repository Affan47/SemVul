ifo_print_subp_attributes(int level, subp_attr_t *attr) {

  if(attr->type == 0
     && attr->lang_code == 0
     && attr->zero1 == 0
     && attr->zero2 == 0
     && attr->lang_extension== 0) {
    printf("-- Unspecified --");
    return;
  }

  printf("type %02x ", attr->type);

  if(isalpha((int)(attr->lang_code >> 8))
     && isalpha((int)(attr->lang_code & 0xff))) {
    printf("%c%c ", attr->lang_code >> 8, attr->lang_code & 0xff);
  } else {
    printf("%02x%02x ", 0xff & (unsigned)(attr->lang_code >> 8),
           0xff & (unsigned)(attr->lang_code & 0xff));
  }

  printf("%d ", attr->zero1);
  printf("%d ", attr->zero2);

  switch(attr->lang_extension) {
  case 0:
    printf("Not specified ");
    break;
  case 1:
    printf("Caption with normal size character ");
    break;
  case 2:
    printf("Caption with bigger size character ");
    break;
  case 3:
    printf("Caption for children ");
    break;
  case 4:
    printf("reserved ");
    break;
  case 5:
    printf("Closed Caption with normal size character ");
    break;
  case 6:
    printf("Closed Caption with bigger size character ");
    break;
  case 7:
    printf("Closed Caption for children ");
    break;
  case 8:
    printf("reserved ");
    break;
  case 9:
    printf("Forced Caption");
    break;
  case 10:
    printf("reserved ");
    break;
  case 11:
    printf("reserved ");
    break;
  case 12:
    printf("reserved ");
    break;
  case 13:
    printf("Director's comments with normal size character ");
    break;
  case 14:
    printf("Director's comments with bigger size character ");
    break;
  case 15:
    printf("Director's comments for children ");
    break;
  default:
    printf("(please send a bug report) ");
  }

}
