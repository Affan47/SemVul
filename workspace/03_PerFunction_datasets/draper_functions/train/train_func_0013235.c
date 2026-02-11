in_border( AW_pos x, AW_pos y, ED4_movemode mode )
{
    AW_pos    world_x, world_y;

    calc_world_coords( &world_x, &world_y );

    switch ( mode )
    {
        case ED4_M_HORIZONTAL:
            {
                if ( (x >= world_x) && (x < (world_x + extension.size[WIDTH])) )
                    return ( 1 );
                break;
            }
        case ED4_M_VERTICAL:
            {
                if ( (y >= world_y) && (y < (world_y + extension.size[HEIGHT])) )
                    return ( 1 );
                break;
            }
        case ED4_M_FREE:
            {
                return ( in_border( x, y, ED4_M_HORIZONTAL ) && in_border( x, y, ED4_M_VERTICAL ) );
            }
        case ED4_M_NO_MOVE:
            {
                break;
            }
    }

    return ( 0 );
}
