iFlipNewBuffer(ILubyte *buff, ILuint depth, ILuint line_size, ILuint line_num)
{
	ILubyte *data;
	ILubyte *s1, *s2;
	ILuint y, d;
	const ILuint size = line_num * line_size;

	if ((data = (ILubyte*)ialloc(depth*size)) == NULL)
		return IL_FALSE;

	for (d = 0; d < depth; d++) {
		s1 = buff + d * size;
		s2 = data + d * size+size;

		for (y = 0; y < line_num; y++) {
			s2 -= line_size;
			memcpy(s2,s1,line_size);
			s1 += line_size;
		}
	}
	return data;
}
