CompRanksOrd( const void* a1, const void* a2 )
{
    int ret;
    ret = (int)pn_RankForSort[(int)*(const AT_RANK*)a1] -
          (int)pn_RankForSort[(int)*(const AT_RANK*)a2];
    if ( !ret )
        ret = (int)*(const AT_RANK*)a1 - (int)*(const AT_RANK*)a2;
    return ret;
}
