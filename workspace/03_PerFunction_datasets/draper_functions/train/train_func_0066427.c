sys_dlcallback( value nargs ) {
	switch( Int_val(nargs) ) {
	case 0:
		return (value)__callb0;
	case 1:
		return (value)__callb1;
	case 2:
		return (value)__callb2;
	case 3:
		return (value)__callb3;
	default:
		failwith("dlcallback(too_many_args)");
	}
	return Val_unit;
}
