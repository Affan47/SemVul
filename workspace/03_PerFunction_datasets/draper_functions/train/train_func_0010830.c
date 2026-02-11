seek(FileOfs o)
{
	if (o<ofs) throw IOException(EINVAL);
	pos = o-ofs;
}
