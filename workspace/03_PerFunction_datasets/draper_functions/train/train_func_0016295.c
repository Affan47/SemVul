gabufr_print_dset(gabufr_dset * dset) {
  gabufr_msg * msg;
  gabufr_val * val;
  gabufr_varinf *varinf=NULL;
  gaint i;

  for (msg = dset->msgs; msg != NULL; msg = msg->next) {
    printf("\n\nmsg %d:\n", msg->fileindex);
    for (i = 0; i < msg->subcnt; i++) {
      printf("\nsubset %d:\n", i);
      for (val = msg->subs[i]; val != NULL; val = val->next) {
	printf("%d (%d) [%.3d]    0-%.2d-%.3d     ", msg->fileindex,
	       i, val->z, val->x, val->y);
	if (val->sval) {
	  printf("[%s]", val->sval);
	} else {
	  if (val->undef) {
	    printf("undef (%g)", val->val);
	  } else {
	    printf("%g", val->val);
	  }
	}
	if ( gabufr_valid_varid(0, val->x, val->y)
	     && varinf == gabufr_get_varinf(val->x, val->y)) {
	  printf("\t\t(%s)", varinf->description);
	}
	printf("\n");
      }
    }
  }
}
