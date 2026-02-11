pinfo(int isitems, int items, int vitems,
		  Type type, Category category, int rank, int *shape)
{
    int i;
    char tbuf[32];
    char mbuf[256];

    mbuf[0] = '\0';

    if (isitems) {
	if (items != vitems)
	    sprintf(mbuf, "There %s %d data item%s (%d valid), each is of type ",
		    (items==1 ? "is" : "are"), items, (items==1 ? "" : "s"),
		    vitems);
	else
	    sprintf(mbuf, "There %s %d data item%s, each is of type ",
		    (items==1 ? "is" : "are"), items, (items==1 ? "" : "s") );
    } else
	strcpy(mbuf, "Each item data type is ");

    switch (rank) {
      case 0:

	break;
      case 1:
	sprintf(tbuf, "%d-vector, ", shape[0]);
	strcat(mbuf, tbuf);
	break;
      case 2:
	sprintf(tbuf,  "%d by %d matrix, ", shape[0], shape[1]);
	strcat(mbuf, tbuf);
	break;
      default:
	sprintf(tbuf,  "%d ", shape[0]);
	strcat(mbuf, tbuf);
	for(i=1; i < rank; i++) {
	    sprintf(tbuf,  "by %d ", shape[i]);
	    strcat(mbuf, tbuf);
	}
	strcat(mbuf,  "tensor, ");
	break;
    }

    switch (category) {
      case CATEGORY_REAL:
	break;
      case CATEGORY_COMPLEX:
	strcat(mbuf,  "complex, "); break;
      case CATEGORY_QUATERNION:
	strcat(mbuf,  "quaternion, "); break;
      default:
	strcat(mbuf,  "unrecognized, "); break;
    }

    switch (type) {
      case TYPE_STRING:
	strcat(mbuf,  "string (a list of characters).\n"); break;
      case TYPE_SHORT:
	strcat(mbuf,  "short integer (2-byte or int*2).\n"); break;
      case TYPE_INT:
	strcat(mbuf,  "integer (4-byte or int*4).\n"); break;
      case TYPE_HYPER:
	strcat(mbuf,  "hyperlong (8-byte or int*8).\n"); break;
      case TYPE_FLOAT:
	strcat(mbuf,  "float (4-byte or real*4).\n"); break;
      case TYPE_DOUBLE:
	strcat(mbuf,  "double (8-byte or real*8).\n"); break;
      case TYPE_UINT:
	strcat(mbuf,  "unsigned integer (4-byte or int*4).\n"); break;
      case TYPE_USHORT:
	strcat(mbuf,  "unsigned short (2-byte or int*2).\n"); break;
      case TYPE_UBYTE:
	strcat(mbuf,  "unsigned byte (1-byte or int*1).\n"); break;
      case TYPE_BYTE:
	strcat(mbuf,  "byte (1-byte or int*1).\n"); break;
      default:
	strcat(mbuf,  "unrecognized.\n"); break;
    }

    DescribeMsg(mbuf);
    return;
}
