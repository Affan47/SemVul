status_string(GcxPar p)
{
	if (PAR(p)->flags & PAR_USER) {
		return "User Set";
	} else if (PAR(p)->flags & PAR_FROM_RC) {
		return "From File";
	} else {
		return "Default";
	}
}
