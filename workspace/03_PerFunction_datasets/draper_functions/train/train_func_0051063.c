computeLengthSpec( const LengthSpec &spec ) const {

    if( spec.displaySizeFactor == 0.0 ) {
        return spec.length;
    } else {
        double tem = format().FotCurDisplaySize * spec.displaySizeFactor;
        return spec.length + long( tem >= 0.0 ? tem +.5 : tem - .5 );
    }
}
