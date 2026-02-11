testTriangle(const SpatialVector & v0,
                          const SpatialVector & v1,
                          const SpatialVector & v2,
                          int vsum) {

    if(vsum == 1 || vsum == 2) return pARTIAL;


    if(vsum == 3) {
        if(sign_ == pOS || sign_ == zERO) return fULL;
        if ( testHole(v0,v1,v2) ) return pARTIAL;
        if ( testEdge(v0,v1,v2) ) return pARTIAL;
        return fULL;
    }


    if ( !testBoundingCircle(v0,v1,v2) ) return rEJECT;

    if ( sign_ == pOS || sign_ == mIXED || (sign_ == zERO && constraints_.size() <= 2)) {

        if ( testEdgeConstraint(v0,v1,v2,0) ) {


            size_t cIndex;
            if ( (cIndex = testOtherPosNone(v0,v1,v2)) ) {

                if ( testConstraintInside(v0,v1,v2, cIndex) )
                    return pARTIAL;

                else if( constraints_[cIndex].contains(v0) )
                    return pARTIAL;
                else return rEJECT;

            } else {
                if(sign_ == pOS || sign_ == zERO) return pARTIAL;
                else return dONTKNOW;
            }
        } else {
            if (sign_ == pOS || sign_ == zERO) {

                if( testConstraintInside(v0,v1,v2, 0) )
                    return pARTIAL;
                else return rEJECT;
            } else return  dONTKNOW;
        }
    } else if (sign_ == zERO) {
        if ( corners_.size() > 0 && testEdge0(v0,v1,v2) )
            return pARTIAL;
        else return rEJECT;
    }
    return pARTIAL;
}
