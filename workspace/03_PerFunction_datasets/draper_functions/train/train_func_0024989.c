update(const MemoryRegion &a)
{
	SecureArray out;
	if(d->done)
		return out;
	d->ok = static_cast<CipherContext *>(context())->update(a, &out);
	return out;
}
