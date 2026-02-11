chsign(Blk *p)
{
	int carry;
	char ct;

	carry=0;
	rewind(p);
	while(sfeof(p) == 0) {
		ct=100-slookc(p)-carry;
		carry=1;
		if(ct>=100) {
			ct -= 100;
			carry=0;
		}
		salterc(p,ct);
	}
	if(carry != 0) {
		sputc(p,-1);
		fsfile(p);
		backc(p);
		ct = sbackc(p);
		if(ct == 99 ) {
			truncate(p);
			sputc(p,-1);
		}
	} else{
		fsfile(p);
		ct = sbackc(p);
		if(ct == 0)
			truncate(p);
	}
	return;
}
