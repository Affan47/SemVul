create_map( vorbis_context * vc, uint_fast8_t floor_number )
{
    vorbis_floor * floors=vc->floors;
    vorbis_floor0 * vf;
    int idx;
    int_fast8_t blockflag;
    int_fast32_t * map;
    int_fast32_t n;

    for (blockflag=0;blockflag<2;++blockflag)
    {
    n=vc->blocksize[blockflag]/2;
    floors[floor_number].data.t0.map[blockflag]=
        av_malloc((n+1) * sizeof(int_fast32_t));

    map=floors[floor_number].data.t0.map[blockflag];
    vf=&floors[floor_number].data.t0;

    for (idx=0; idx<n;++idx) {
        map[idx]=floor( BARK((vf->rate*idx)/(2.0f*n)) *
                              ((vf->bark_map_size)/
                               BARK(vf->rate/2.0f )) );
        if (vf->bark_map_size-1 < map[idx]) {
            map[idx]=vf->bark_map_size-1;
        }
    }
    map[n]=-1;
    vf->map_size[blockflag]=n;
    }

#   ifdef V_DEBUG
    for(idx=0;idx<=n;++idx) {
        AV_DEBUG("floor0 map: map at pos %d is %d\n",
                 idx, map[idx]);
    }
#   endif
}
