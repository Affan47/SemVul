blendNoise1d( double x,
                     unsigned int y,
                     unsigned int z,
                     unsigned int t ) {

    double floorX = floor( x );
    unsigned int floorIntX = (unsigned int)floorX;

    if( floorX == x ) {
        unsigned int precomputedMix = mixFour( floorIntX, y, z, t );

        return noise1dInt32( precomputedMix );
        }
    else {
        unsigned int ceilIntX = floorIntX + 1;


        double ft = ( x - floorX ) * M_PI;
        double f = ( 1 - cos( ft ) ) * .5;


        unsigned int precomputedMix = mixFour( floorIntX, y, z, t );
        double valueAtFloor = noise1dInt32( precomputedMix );

        precomputedMix = mixFour( ceilIntX, y, z, t );
        double valueAtCeiling = noise1dInt32( precomputedMix );

        return linearInterpolation( f, valueAtFloor, valueAtCeiling );
        }
    }
