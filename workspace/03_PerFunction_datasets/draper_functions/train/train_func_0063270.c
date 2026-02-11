popch() {


	if (occupation) return '\0';
	if (in_doagain) return(char)((shead != stail) ? saveq[stail++] : '\0');
	else		return(char)((phead != ptail) ? pushq[ptail++] : '\0');
}
