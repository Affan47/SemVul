LoadDXT5( QDataStream & s, const DDSHeader & header, QImage & img )
{
    const uint w = header.width;
    const uint h = header.height;

    BlockDXT block;
    BlockDXTAlphaLinear alpha;
    QRgb * scanline[4];

    for( uint y = 0; y < h; y += 4 ) {
        for( uint j = 0; j < 4; j++ ) {
            scanline[j] = (QRgb *) img.scanLine( y + j );
        }
        for( uint x = 0; x < w; x += 4 ) {


            s >> alpha;
            s >> block;


            Color8888 color_array[4];
            block.GetColors(color_array);

            uchar alpha_array[8];
            alpha.GetAlphas(alpha_array);

            uchar bit_array[16];
            alpha.GetBits(bit_array);


            const uint masks[4] = { 3, 3<<2, 3<<4, 3<<6 };
            const int shift[4] = { 0, 2, 4, 6 };


            for( uint j = 0; j < 4; j++ ) {
                for( uint i = 0; i < 4; i++ ) {
                    if( img.valid( x+i, y+j ) ) {
                        uint idx = (block.row[j] & masks[i]) >> shift[i];
                        color_array[idx].a = alpha_array[bit_array[j*4+i]];
                        scanline[j][x+i] = qRgba(color_array[idx].r, color_array[idx].g, color_array[idx].b, color_array[idx].a);
                    }
                }
            }
        }
    }

    return true;
}
