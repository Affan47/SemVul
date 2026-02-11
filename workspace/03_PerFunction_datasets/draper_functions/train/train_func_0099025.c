Peek32u(LFA_FileRef file, bool bigEndian = false )
{
	XMP_Uns32 value = tree->digest32u(file, "", bigEndian );
	Rewind(file, 4);
	return value;
}
