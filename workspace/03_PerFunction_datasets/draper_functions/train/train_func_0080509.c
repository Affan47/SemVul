find(const fxStr& s, fxStr* name)
{
    fxStr canon(s);
    canon.lowercase();
    for (u_int l = 0; l < canon.length(); l = canon.next(l, "+?*[].\\")) {
	canon.insert('\\', l);
	l += 2;
    }
    RE pat(canon);
    for (FaxInfoDictIter iter(dict); iter.notDone(); iter++) {
	fxStr t(iter.key());
	t.lowercase();
	if (pat.Find(t)) {
	    if (name)
		*name = iter.key();
	    return (iter.value());
	}
    }
    return (0);
}
