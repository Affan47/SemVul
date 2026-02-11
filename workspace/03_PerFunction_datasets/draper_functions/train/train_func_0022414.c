listTyvars(t,o,ns)
Cell t;
Int  o;
List ns; {
    switch (whatIs(t)) {
	case AP        : return listTyvars(fst(t),o,
				 listTyvars(snd(t),o,
				  ns));
	case OFFSET    : return listTyvar(o+offsetOf(t),ns);
	case INTCELL   : return listTyvar(intOf(t),ns);
	default        : break;
    }
    return ns;
}
