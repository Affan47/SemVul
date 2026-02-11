TTYshow(ECHAR c)
{
    if (c == DEL) {
	TTYput('^');
	TTYput('?');
    }
    else if (ISCTL(c)) {
	TTYput('^');
	TTYput(UNCTL(c));
    }
    else if (rl_meta_chars && ISMETA(c)) {
	TTYput('M');
	TTYput('-');
	TTYput(UNMETA(c));
    }
    else
	TTYput(c);
}
