write_bilevel_ascii()
    {

        typedef void_vector< UInt8 > vector_type;
        vector_type & cbands = static_cast< vector_type & >(bands);


        UInt8 * iter = cbands.data();
        for( unsigned int i = 0; i < height; ++i ) {
            for ( unsigned int j = 0; j < width; ++j ) {
                for ( unsigned int k = 0; k < components; ++k ) {
                    const int value = *iter / 255;
                    ++iter;
                    stream << value + '0' << " ";
                }
                stream << " ";
            }
            stream << std::endl;
        }
    }
