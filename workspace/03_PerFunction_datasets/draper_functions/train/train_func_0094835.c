writeValue(OFile *fp, VObject *o, unsigned long size,int quote)
{
    if (o == 0) return;
    switch (VALUE_TYPE(o)) {
	case VCVT_USTRINGZ: {
	    char *s = fakeCString(USTRINGZ_VALUE_OF(o));
	    if(quote) writeQPString(fp, s);
	    else writeString(fp,s);
	    deleteStr(s);
	    break;
	    }
	case VCVT_STRINGZ: {
	    if(quote) writeQPString(fp, STRINGZ_VALUE_OF(o));
	    else writeString(fp,STRINGZ_VALUE_OF(o));
	    break;
	    }
	case VCVT_UINT: {
	    char buf[16];
	    snprintf(buf,sizeof(buf),"%u", INTEGER_VALUE_OF(o));
	    appendsOFile(fp,buf);
	    break;
	    }
	case VCVT_ULONG: {
	    char buf[16];
	    snprintf(buf,sizeof(buf),"%lu", LONG_VALUE_OF(o));
	    appendsOFile(fp,buf);
	    break;
	    }
	case VCVT_RAW: {
	    appendcOFile(fp,'\n');
	    writeBase64(fp,(unsigned char*)(ANY_VALUE_OF(o)),size);
	    break;
	    }
	case VCVT_VOBJECT:
	    appendcOFile(fp,'\n');
	    writeVObject_(fp,VOBJECT_VALUE_OF(o));
	    break;
	}
}
