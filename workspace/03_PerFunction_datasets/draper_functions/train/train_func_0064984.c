fmtlocaleinit(Fmt *f, char *decimal, char *thousands, char *grouping)
{
	if(decimal == nil || decimal[0] == '\0')
		decimal = ".";
	if(thousands == nil)
		thousands = ",";
	if(grouping == nil)
		grouping = "\3";
	f->decimal = decimal;
	f->thousands = thousands;
	f->grouping = grouping;
}
