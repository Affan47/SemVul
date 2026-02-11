step_segmenter( Segmenter *s, const unsigned char *source, int width, int height  )
{
    if(  s->region_refs && s->regions && s->regions_under_construction )
        build_regions( s, source, width, height );
}
