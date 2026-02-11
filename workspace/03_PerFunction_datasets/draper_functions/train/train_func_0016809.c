separator_proc(c)
     Character *c;
{
    int i;
    int flag = 1;

    switch(c->type) {
      case OTHER:
      case ASCII:
      case JISROMAN:
	switch(c->c1) {
	  case ' ':
	  case '\011':
	  case '\015':
	    separator_out = 0;
	    return;
	}


	for (i=0; i<KAKASIBUF && separator[i].c1 != 0; i++) {
	    if ((c+i)->c1 != separator[i].c1 ||
		(c+i)->c2 != separator[i].c2) {
		flag = 0;
		break;
	    }
	}
	if (flag) {
	    separator_out = 0;
	    return;
	}
    }

    if (separator_out != 2) {
	separator_out = 1;
	return;
    }


    for (i=0; i<KAKASIBUF && separator[i].c1 != 0; i++) {
	putkanji(&separator[i]);
    }

    separator_out = 1;
}
