CompareNeighListLex( NEIGH_LIST pp1, NEIGH_LIST pp2, const AT_RANK *nRank)
{
    int len1 = (int)*pp1++;
    int len2 = (int)*pp2++;
    int len  = inchi_min( len1, len2 );
    int diff = 0;
    while ( len -- > 0 && !( diff = (int)nRank[*pp1++] - (int)nRank[*pp2++] ) )
        ;
    return diff? diff : (len1 - len2);

}
