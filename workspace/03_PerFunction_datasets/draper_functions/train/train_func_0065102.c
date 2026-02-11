ReadJPEGData( std::ifstream& jpeg_in, int& image_width, int& image_height,
                   int& image_colorspace, int& bitspercomponent )
{
    int required_segments = 0;
    try {
        const unsigned int soi = JPEG_read2(jpeg_in);
        if( (soi & 0xFF) != jpeg_SOI )
            return false;

        while( required_segments != 3 && !jpeg_in.eof() ) {
            const unsigned int marker = JPEG_next_marker(jpeg_in);
            switch( marker ) {
            case jpeg_APP0: {
                unsigned int l = JPEG_read2(jpeg_in);
                const char* JFIF = "JFIF";
                for( int i=0; i<5; ++i )
                    if( JFIF[i] != (int)JPEG_read1(jpeg_in) )
                        return false;
                jpeg_in.seekg( l-5-2, std::ios::cur );

                required_segments |= 1;
                break;
            }
            case jpeg_SOF0:
            case jpeg_SOF1:
            case jpeg_SOF2:
            case jpeg_SOF3: {
                unsigned int l = JPEG_read2(jpeg_in);
                bitspercomponent = JPEG_read1(jpeg_in);
                image_height = JPEG_read2(jpeg_in);
                image_width  = JPEG_read2(jpeg_in);
                unsigned int ncomponents = JPEG_read1(jpeg_in);
                switch( ncomponents ) {
                case 1: image_colorspace = IMAGE_GRAY; break;
                case 3: image_colorspace = IMAGE_RGB;  break;
                case 4: image_colorspace = IMAGE_CMYK; break;
                default:
                    return false;
                }
                if( l != 8 + 3*ncomponents )
                    throw std::string("Unexpected SOFx length.");

                required_segments |= 2;
                break;
            }
            default:
                JPEG_skip_segment(jpeg_in);
            }
        }
    } catch( std::string msg ) {
        fprintf(stderr, "Error while reading JPEG: %s.\n", msg.c_str() );
    }
    return required_segments == 3;
}
