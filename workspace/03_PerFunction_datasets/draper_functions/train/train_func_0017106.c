twlen0(INT r, const tw_instr *p, INT *vl)
{
     INT ntwiddle = 0;


     A(r > 0);
     for ( ; p->op != TW_NEXT; ++p) {
	  switch (p->op) {
	      case TW_FULL:
		   ntwiddle += (r - 1) * 2;
		   break;
	      case TW_HALF:
		   ntwiddle += (r - 1);
		   break;
	      case TW_CEXP:
		   ntwiddle += 2;
		   break;
	      case TW_COS:
	      case TW_SIN:
		   ntwiddle += 1;
		   break;
	  }
     }

     *vl = (INT)p->v;
     return ntwiddle;
}
