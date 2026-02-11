DitherLine( HTONE *htone, int y )
{
int		x;
int		pixel;
int		length;
byte	*res;
byte	*data;
byte	*block;
byte	*matrix;
int		mx;
int		lval, hval;

        length  = htone->render->width;

        res		= htone->res;
        data	= htone->data;
        block	= htone->block;

        matrix	= dmatrix[ y % DMATRIX_Y ];

        for ( mx = x = 0 ; x < length ; x++ ) {


                *res = 0;


                if ( ( pixel = *data ) > htone->mval ) {

                        lval = htone->mval;
                        hval = 255;

                        if ( htone->mval == 127 )

                                pixel = ( ( pixel - htone->mval ) * 2 - 1 ) / 2;
                        else
                                pixel = ( pixel - htone->mval ) * 255 / ( 255 - htone->mval );
                }
                else {

                        lval = 0;
                        hval = htone->mval;

                        if ( htone->mval != 255 ) {

                                if ( htone->mval == 127 )

                                        pixel = ( pixel * 4 + 1 ) / 2;
                                else
                                        pixel = pixel * 255 / htone->mval;
                        }
                }

                if ( block && *block ) {

                        *res = 0;
                }
                else {

                        if ( pixel >= matrix[ mx ] )

                                *res = hval;
                        else
                                *res = lval;
                }

                res++;
                if ( ++mx == DMATRIX_X ) mx = 0;
                if ( block ) block++;
                data += htone->step;
        }
}
