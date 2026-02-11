intersect(const SpatialIndex * idx, HtmRange * htmrange)
{
    hr = htmrange;
    index_ = idx;
    addlevel_ = idx->maxlevel_ - idx->buildlevel_;

    simplify();

    if(constraints_.empty())return;


    for(uint32 i = 1; i <= 8; i++){
        testTrixel(i);
    }
}
