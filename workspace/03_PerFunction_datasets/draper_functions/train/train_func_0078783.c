combine( const EffectiveDisplaySpace eds ) {

    if( eds.force ) {
        if( force ) {
            nominal += eds.nominal;
            min += eds.min;
            max += eds.max;
        } else
            *this = eds;
    } else {
        if( eds.priority > priority )
            *this = eds;
        else {
            if( eds.priority == priority ) {
                if( eds.nominal > nominal )
                    *this = eds;
                else
                    if( eds.nominal == nominal ) {
                        if( eds.min < min ) {
                            min = eds.min;
                        }
                        if( eds.max > max ) {
                            max = eds.max;
                        }
                    }
            }
        }
    }
}
