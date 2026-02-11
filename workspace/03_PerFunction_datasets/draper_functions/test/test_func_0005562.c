s_path(cbuf)

char *cbuf;
{
    int pathwidth = 0;
    int ptype = 0;
    int i;
    int type;
    int ncoords = 0;
    int dtype = CurrentDataType;
    int layer = CurrentLayer;

    while ((type = get_record(cbuf)) != ENDEL) {
        switch(type) {

        case LAYER:
            layer = strm_ival(cbuf);
            break;

        case DATATYPE:
            dtype = strm_ival(cbuf);
            break;

        case WIDTH:
            pathwidth = LONGSCALE( strm_longval(cbuf) );
            break;

        case XY:
            ncoords = CurrentSize/4;
            for (i = 0; i < ncoords; ++i)
                XYbuf[i] = LONGSCALE( strm_longval(cbuf + (i << 2)) );
            ncoords /= 2;
            break;

        case PATHTYPE:


            if ((ptype = strm_ival(cbuf)) != 2)
                fprintf(SymDesc,"( PATHTYPE %d CONVERTED TO PATHTYPE 2 );\n",ptype);
            break;

        case PROPATTR:
            CurrentAttribute = strm_ival(cbuf);
            break;

        case PROPVALUE:
            CurrentAttribute = -1;
            break;

        default:
            err_fatal_2("Illegal record type",type);
        }
    }
    print_layer(layer,dtype);
    if (ptype == 0 && ncoords > 1) {


        ConvertPathtype(&XYbuf[0],&XYbuf[1],XYbuf[2],XYbuf[3],pathwidth,0);
        i = ncoords+ncoords-2;
        ConvertPathtype(&XYbuf[i],&XYbuf[i+1],XYbuf[i-2],XYbuf[i-1],pathwidth,0);
    }
    if (ptype != 2)
        fprintf(SymDesc,"5 %d PATHTYPE %d;\n",PROPERTYOFFSET + PATHTYPE,ptype);

    sprintf(cbuf,"W %d",pathwidth);
    set_path(cbuf,ncoords,XYbuf);
}
