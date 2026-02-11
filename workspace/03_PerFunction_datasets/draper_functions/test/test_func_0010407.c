map_set_fog( int type )
{
    int x, y;
    for ( y = 0; y < map_h; y++ )
        for ( x = 0; x < map_w; x++ )
            switch ( type ) {
                case F_SPOT: mask[x][y].fog = !mask[x][y].spot; break;
                case F_IN_RANGE: mask[x][y].fog = ( (!mask[x][y].in_range && !mask[x][y].sea_embark) || mask[x][y].blocked ); break;
                case F_MERGE_UNIT: mask[x][y].fog = !mask[x][y].merge_unit; break;
                case F_SPLIT_UNIT: mask[x][y].fog = !mask[x][y].split_unit&&!mask[x][y].split_okay; break;
                case F_DEPLOY: mask[x][y].fog = !mask[x][y].deploy; break;
                default: mask[x][y].fog = 0; break;
            }
}
