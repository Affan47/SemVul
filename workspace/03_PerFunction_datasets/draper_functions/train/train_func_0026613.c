IsValid( const DDSHeader & header )
{
    if( header.size != 124 ) {
        return false;
    }
    const uint required = (DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT);
    if( (header.flags & required) != required ) {
        return false;
    }
    if( header.pf.size != 32 ) {
        return false;
    }
    if( !(header.caps.caps1 & DDSCAPS_TEXTURE) ) {
        return false;
    }
    return true;
}
