cut(FileOfs size)
{
	if (!(getAccessMode() & IOAM_WRITE)) throw IOException(EACCES);

	FileOfs o = tell();
	if (o + size > newsize) throw IOException(EINVAL);
	ObjHandle h = findArea(o);
	FileOfs ssize = size;


	while (size) {

		assert(h != invObjHandle)
		FileArea *a = (FileArea*)mods.get(h);
		FileOfs s = o - a->start;
		FileOfs z = a->size - s;
		if (z > size) z = size;
		ObjHandle hnext = mods.findNext(h);
		bool deleted = cut1(h, s, z);

		if (!deleted && o == a->start)
			a->start -= ssize-size;
		o += z;
		size -= z;
		newsize -= z;
		if (deleted) {
			h = findArea(o);
		} else {
			h = hnext;
		}
	}
	while (h != invObjHandle) {
		FileArea *a = (FileArea*)mods.get(h);
		h = mods.findNext(h);
		a->start -= ssize;
	}
	mcount++;
}
