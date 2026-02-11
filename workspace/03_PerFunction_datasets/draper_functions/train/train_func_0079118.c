compare_labeltables(const giiLabelTable *t1, const giiLabelTable *t2,
                               int verb, int approx)
{
    int lverb = verb;
    int c, roff, offset, diffs = 0;

    if( G.verb > lverb ) lverb = G.verb;

    if( !t1 || !t2 ) {
        if(!t1 && !t2) return 0;
        if(lverb>2)
            printf("-- Comp LabTab: have NULL: %p, %p\n",(void*)t1,(void*)t2);
        return 1;
    }


    if( t1->length <= 0 && t2->length <= 0 ) return 0;

    if( t1->length != t2->length ) {
        if(lverb>2)printf("-- labeltable lengths diff: %d vs. %d\n",
                          t1->length, t2->length);
        return 1;
    }


    if( (t1->rgba && !t2->rgba) || (!t1->rgba && t2->rgba) ) {
        if(lverb>2)printf("-- only 1 labeltable has RGBA list\n");
        if(lverb<3) return 1;
    }


    offset = (int)gifti_approx_diff_offset(t1->key, t2->key,
                       t1->length, NIFTI_TYPE_INT32, approx?1.0:0.0);
    if( offset >= 0 ) {
        if(lverb>2)printf("-- labeltable Key diff at index %d\n", offset);
        if(lverb<3) return 1;
        diffs++;
    }


    roff = 0;
    for( c = 0; c < t1->length; c++ ) {
        if( gifti_strdiff(t1->label[c], t2->label[c]) ) {
            if(lverb>2)printf("-- labeltable Label diff at index %d\n", c);
            if(lverb<3) return 1;
            diffs++;
            break;
        }
    }

    if( t1->rgba && t2->rgba ) {

        offset = (int)gifti_approx_diff_offset(t1->rgba, t2->rgba,
                           4*t1->length, NIFTI_TYPE_FLOAT32, approx?1.0:0.0);
        if( offset >= 0 ) {
            offset /= 4;
            if(lverb>2)printf("-- labeltable RGBA diff at index %d\n", offset);
            if(lverb<3) return 1;
            diffs++;
        }
    }

    return diffs;
}
