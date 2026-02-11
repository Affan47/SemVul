depClassBindings(bs)
List bs; {
    for (; nonNull(bs); bs=tl(bs)) {
	if (nonNull(hd(bs))) {
	   mapProc(depAlt,snd(hd(bs)));
	}
    }
}
