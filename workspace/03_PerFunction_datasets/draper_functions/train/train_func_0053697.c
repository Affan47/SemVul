find_fiducialsX( FiducialX *fiducials, int max_count,
        FidtrackerX *ft, Segmenter *segments, int width, int height)
{
    int i = 0;
    Region *next;

    initialize_head_region( &ft->root_regions_head );

    find_roots( segments, ft);

    next = ft->root_regions_head.next;
    while( next != &ft->root_regions_head ){

        compute_fiducial_statistics( ft, &fiducials[i], next, width, height );

        next = next->next;
        ++i;
        if( i >= max_count )
            return i;
    }

    return i;
}
