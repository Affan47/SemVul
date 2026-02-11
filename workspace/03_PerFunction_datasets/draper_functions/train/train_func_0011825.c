_dxfskiparray_text(struct finfo *f, int items, Type type)
{
    Error rc = OK;

    if(items <= 0)
	DXErrorReturn(ERROR_DATA_INVALID, "bad item count");


    _dxfsetskipnum(f, 1);
    _dxfsetdictstringmode(f, 1);


#define GETITEMSX(dtype,dname) \
{ \
    dtype d; \
    int i; \
\
    for(i=0; i<items; i++) { \
        rc = _dxfmatch##dtype(f, &d); \
        if(!rc) { \
            DXSetError(ERROR_DATA_INVALID,  \
                       "error reading text data; item %d, type " dname, i+1); \
            goto error; \
        } \
    } \
}


    switch(type) {
      case TYPE_STRING:
	{
	    int rc, j;

	    for (j=0; j<items; j++) {
		rc = _dxfgetstringnodict(f);
		if (!rc) {
		    DXSetError(ERROR_DATA_INVALID,
		       "error reading text data; item %d, type string",  j+1);
		    goto error;
		}
	    }

        }
	break;

      case TYPE_UBYTE:
        GETITEMSX(ubyte, "unsigned byte")
	break;

      case TYPE_BYTE:
        GETITEMSX(byte, "signed byte")
	break;

      case TYPE_SHORT:
        GETITEMSX(short, "short");
        break;

      case TYPE_USHORT:
        GETITEMSX(ushort, "unsigned short");
        break;

      case TYPE_INT:
        GETITEMSX(int, "integer");
        break;

      case TYPE_UINT:
        GETITEMSX(uint, "unsigned integer");
        break;

      case TYPE_FLOAT:
        GETITEMSX(float, "float");
        break;

      case TYPE_DOUBLE:
        GETITEMSX(double, "double");
        break;

      default:
	DXSetError(ERROR_NOT_IMPLEMENTED, "unsupported data type");
	break;

    }

 error:
    _dxfsetskipnum(f, 0);
    _dxfsetdictstringmode(f, 0);

    return rc;
}
