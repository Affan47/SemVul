create_cursor( int width, int height, int hot_x, int hot_y, const char *source )
{
    unsigned char *mask = 0, *data = 0;
    SDL_Cursor *cursor = 0;
    int i, j, k;
    char data_byte, mask_byte;
    int pot;


    mask = malloc( width * height * sizeof ( char ) / 8 );
    data = malloc( width * height * sizeof ( char ) / 8 );

    k = 0;
    for (j = 0; j < width * height; j += 8, k++) {

        pot = 1;
        data_byte = mask_byte = 0;

        for (i = 7; i >= 0; i--) {

            switch ( source[j + i] ) {

                case 'b':
                    data_byte += pot;
                case 'w':
                    mask_byte += pot;
                    break;

            }
            pot *= 2;

        }

        data[k] = data_byte;
        mask[k] = mask_byte;

    }


    cursor = SDL_CreateCursor( data, mask, width, height, hot_x, hot_y );
    free( mask );
    free( data );
    return cursor;
}
