line_intersect( Line *line, Line *target, Coord *pos )
{

    pos->x = pos->y = 0;

    if ( line->vertical && target->vertical ) return 0;
    if ( !line->vertical &&  !target->vertical && line->m == target->m ) return 0;

    if ( line->m == 0 && line->vertical == 0 ) {
        pos->y = line->n;
        if ( target->vertical )
            pos->x = target->x;
        else
            pos->x = ( pos->y - target->n ) / target->m;
        return 1;
    }
    if ( line->vertical ) {
        if ( target->vertical ) return 0;
        pos->x = line->x;
        pos->y = target->m * pos->x + target->n;
        return 1;
    }
    if ( target->vertical ) {
        printf( "line_intersect: line non-vertical and target vertical not supported yet\n" );
        return 1;
    }

    pos->x = ( line->n - target->n ) / ( target->m - line->m );
    pos->y = line->m * pos->x + line->n;
    return 1;
}
