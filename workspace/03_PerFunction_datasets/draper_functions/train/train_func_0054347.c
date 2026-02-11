get_knr_args(Ident *ident)
{
     int parmcnt, stop;
     Stackpos sp, new_sp;
     Ident id;

     switch (tok.type) {
     case IDENTIFIER:
     case TYPE:
     case STRUCT:


	  mark(sp);
	  parmcnt = 0;

	  for (stop = 0; !stop && parmcnt < ident->parmcnt;
	       nexttoken()) {
	       id.type_end = -1;
	       switch (tok.type) {
	       case LBRACE:
	       case LBRACE0:
		    putback();
		    stop = 1;
		    break;
	       case TYPE:
	       case IDENTIFIER:
	       case STRUCT:
		    putback();
		    mark(new_sp);
		    if (dcl(&id) == 0) {
			 parmcnt++;
			 if (tok.type == ',') {
			      do {
				   tos = id.type_end;
				   restore(new_sp);
				   dcl(&id);
			      } while (tok.type == ',');
			 } else if (tok.type != ';')
			      putback();
			 break;
		    }


	       default:
		    restore(sp);
		    return 1;
	       }
	  }
     }
     return 0;
}
