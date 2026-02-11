lowerBound(const QList<SmartRange*>& ranges, const Cursor& pos)
{
    int begin = 0;
    int n = ranges.count();

    int half;
    int middle;

    while (n > 0) {
        half = n >> 1;
        middle = begin + half;
        if(ranges[middle]->end() > pos) {
          n = half;
        }else{
          begin = middle + 1;
          n -= half + 1;
        }
    }
    return begin;
}
