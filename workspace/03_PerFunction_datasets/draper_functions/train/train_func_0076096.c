get_z_coord( inp_ATOM* at, int cur_atom, int neigh_no,  int *nType, int bPointedEdgeStereo )
{
    int stereo_value = at[cur_atom].bond_stereo[neigh_no];
    int stereo_type  = abs( stereo_value );
    int neigh        = (int)at[cur_atom].neighbor[neigh_no];
    double z         = at[neigh].z - at[cur_atom].z;
    int    bFlat;

    if ( bFlat = (fabs(z) < ZERO_LENGTH) ) {
        int i;
        for ( i = 0; i < at[cur_atom].valence; i ++ ) {
            if ( fabs(at[cur_atom].z - at[(int)at[cur_atom].neighbor[i]].z) > ZERO_LENGTH ) {
                bFlat = 0;
                break;
            }
        }
    }

    if ( bFlat ) {
        if ( !bPointedEdgeStereo || bPointedEdgeStereo * stereo_value >= 0 ) {


            switch( stereo_type ) {

            case 0:
                *nType = ZTYPE_NONE;
                break;
            case STEREO_SNGL_UP:
                *nType = ZTYPE_UP;
                break;
            case STEREO_SNGL_EITHER:
                *nType = ZTYPE_EITHER;
                break;
            case STEREO_SNGL_DOWN:
                *nType = ZTYPE_DOWN;
                break;
            default:
                *nType = ZTYPE_NONE;
            }
            if ( stereo_value < 0 && (*nType == ZTYPE_DOWN || *nType == ZTYPE_UP) )
                *nType = -*nType;
        } else {
            *nType = ZTYPE_NONE;
        }
    } else
    if ( stereo_type == STEREO_SNGL_EITHER &&
         ( !bPointedEdgeStereo || bPointedEdgeStereo * stereo_value >= 0 ) ) {
        *nType = ZTYPE_EITHER;
    } else {
        *nType = ZTYPE_3D;
    }
    return z;
}
