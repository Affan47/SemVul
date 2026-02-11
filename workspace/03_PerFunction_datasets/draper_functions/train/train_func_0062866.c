open_tif_input_file(context *con)
{
    int i, one=1;
    uint16_t magic, nentry, tag, type;
    uint32_t count, diroff;

    rewind(con->file);
    read_uint16(con, &magic, 1);
    switch (magic) {
        case 0x4949 : con->swap = *(char*)&one!=1; break;
        case 0x4d4d : con->swap = *(char*)&one==1; break;
        default : error("bad magic number 0x%04x found at start of TIFF file %s", magic, con->name);
    }
    read_uint16(con, &magic, 1);
    if (magic!=42)
        error("magic number 42 not found in TIFF file %s", con->name);
    read_uint32(con, &diroff, 1);

    seek_file(con, diroff, SEEK_SET);
    read_uint16(con, &nentry, 1);
    for (i=0; i<nentry; i++) {
        int ifdoff = diroff+2+12*i;
        read_tif_ifd_entry(con, ifdoff, &tag, &type, &count);
        uint32_t data = read_tif_datum(con, type, count, 0);
        switch (tag) {
            case ImageWidth:
                con->wid = data;
                break;
            case ImageLength:
                con->hei = data;
                break;
            case BitsPerSample:
                con->bpi = data;
                break;
            case SamplesPerPixel:
                con->ncomp = data;
                break;
            case Compression:
                if (data!=1)
                    error("TIFF input file %s is compressed", con->name);
                break;
            case StripOffsets:
                con->nstrips = count;
                con->offoff = ifdoff;
                break;
            case RowsPerStrip:
                con->nlines = data;
                break;
            case SampleFormat:
                con->sf = data;
                break;
            case Photometric:
                con->photometric = data;
                break;

        }
    }

    if (con->wid<=0)
        error("valid ImageWidth entry not found in directory of TIFF file %s", con->name);
    if (con->hei<=0)
        error("valid ImageLength entry not found in directory of TIFF file %s", con->name);
    if (con->ncomp!=1 && con->ncomp!=3 && con->ncomp!=4 && con->ncomp!=5)
        error("valid SamplesPerPixel entry (1, 3, 4, or 5) not found in directory of TIFF file %s", con->name);
    if (con->bpi>32)
        error("valid BitsPerSample entry not found in directory of TIFF file %s", con->name);
    if (con->nstrips<=0 || con->offoff==0)
        error("valid StripOffsets entry not found in directory of TIFF file %s", con->name);
    if (con->nlines<=0)
        error("valid RowsPerStrip entry not found in directory of TIFF file %s", con->name);
    con->line = con->nlines;
}
