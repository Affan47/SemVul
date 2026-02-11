is_adjacent( Region* r1, Region* r2 )
{


    int i;


    if( r1->adjacent_region_count > r2->adjacent_region_count ){
        Region *temp = r1;
        r1 = r2;
        r2 = temp;
    }

    for( i=0; i < r1->adjacent_region_count; ++i )
        if( r1->adjacent_regions[i] == r2 )
            return 1;

    return 0;
}
