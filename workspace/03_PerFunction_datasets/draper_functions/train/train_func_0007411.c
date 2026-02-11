NextListItem(const char *s, int *index,
				Type listtype, char *buf, int bufsz)
{
    int start, i = *index;
    boolean r = true;
    char *p ;

    if (!s)
	return NULL;

    ASSERT(listtype & DXType::ListType);


    if (i < 0) {
	i = 0;
	SkipWhiteSpace(s,i);
	if (s[i] != '{')
	    return NULL;
	i++;
    	SkipWhiteSpace(s,i);
    } else {
    	SkipWhiteSpace(s,i);
	if (s[i] == ',') {
	    i++;
	    SkipWhiteSpace(s,i);
	}
    }

    start = i;
    int tuple;
    switch (listtype & DXType::ListTypeMask) {
	case DXType::ScalarType:
	    r = IsScalar(s, i);
	    break;
	case DXType::IntegerType:
	    r = IsInteger(s, i);
	    break;
	case DXType::VectorType:
	    r = IsVector(s, i, tuple);
	    break;
	case DXType::TensorType:
	    r = IsTensor(s, i);
	    break;
	case DXType::StringType:
	    r = IsString(s, i);
	    break;
	case DXType::ValueType:
	    r = IsInteger(s, i) || IsScalar(s,i) || IsVector(s,i,tuple) ||
						    IsTensor(s,i);
	    break;
	default:
	    printf("Can't get list items from a list of type 0x%lx\n",listtype);
	    ASSERT(0);
    }

    p = NULL;
    if (r) {
	p = buf;
	int len = i - start;
	if (!p)
	    p = new char[len + 1];
	else if ((bufsz > 0) && (bufsz < (len+1))) {
	    printf ("%s[%d]Warning: buffer overrun\n", __FILE__,__LINE__);
	}
	strncpy(p,&s[start], len);
	p[len] = '\0';
	*index = i;
    }

    return p;
}
