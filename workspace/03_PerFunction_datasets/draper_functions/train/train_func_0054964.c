s_text(cbuf)

char *cbuf;
{
    double magn = 1,rotn = 0;
    char *cp, string[48];
    int cx = 0,cy = 0;
    int width = 0;
    int ptype = 0;
    int reflection = 0;
    int present = 0;
    int type;
    int dtype = CurrentDataType;
    int layer = CurrentLayer;

    while ((type = get_record(cbuf)) != ENDEL) {
        switch(type) {

        case LAYER:
            layer = strm_ival(cbuf);
            break;

        case WIDTH:
            width = LONGSCALE( strm_longval(cbuf) );
            break;

        case XY:
            cx = LONGSCALE( strm_longval(cbuf) );
            cy = LONGSCALE( strm_longval(cbuf+4) );
            break;

        case TEXTTYPE:
            dtype = strm_ival(cbuf);
            break;

        case PRESENTATION:
            present = strm_ival(cbuf);
            break;

        case STRING:
            cp = cbuf;
            while (*cp != '\0') {
                if (*cp == ' ')
                    *cp = '_';
                cp++;
            }
            strcpy(string,cbuf);
            break;

        case STRANS:
            if (cbuf[1] & 4)
                err_warn_2("Absolute magnification",1,CurrentSymbol);
            if (cbuf[1] & 2)
                err_warn_2("Absolute angle",1,CurrentSymbol);
            if (cbuf[0] & 128)
                reflection = 1;
            else
                reflection = 0;
            break;

        case MAG:
            magn = strm_doubleval(cbuf);
            break;

        case ANGLE:
            rotn = strm_doubleval(cbuf);
            break;

        case PATHTYPE:


            ptype = strm_ival(cbuf);
            break;

        case PROPATTR:
            CurrentAttribute = strm_ival(cbuf);
            break;

        case PROPVALUE:
            set_property_value(cbuf,type);
            break;

        default:
            err_fatal_2("Illegal record type",type);
        }
    }
    PrintLayer(layer,dtype);
    fprintf(SymDesc,
        "5 %d WIDTH %d PRESENT %d PTYPE %d MAG %f ANGLE %f REFLECT %d;\n",
        PROPERTYOFFSET + TEXT,width,present,ptype,magn,rotn,reflection);
    fprintf(SymDesc,"94 %s %d %d;\n",string,cx,cy);
}
