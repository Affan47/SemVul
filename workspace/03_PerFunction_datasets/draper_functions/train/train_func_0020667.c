dbtype(type)
struct typestruct *type;
{
    for ( ; type != NULL; type = type->nexttype)
    {
	outbyte(' ');
	switch (type->constructor)
	{
	case ARRAY:
	    outbyte('[');
	    outhex(type->typesize / type->nexttype->typesize);
	    outbyte(']');
	    break;
	case FUNCTION:
	    outstr("()");
	    break;
	case POINTER:
	    outbyte('*');
	    break;
	case STRUCTU:
	    outstr("struct ");
	default:
	    if (type->scalar & UNSIGNED)
		outstr("unsigned ");
	    outstr(type->tname);
	    break;
	}
    }
}
