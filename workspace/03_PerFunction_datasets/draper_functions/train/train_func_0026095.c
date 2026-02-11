yearStart(int32_t year) const{
    if (cType == CIVIL || cType == TBLA ||
        (cType == UMALQURA && year < UMALQURA_YEAR_START))
    {
        return (year-1)*354 + ClockMath::floorDivide((3+11*year),30);
    } else if(cType==ASTRONOMICAL){
        return trueMonthStart(12*(year-1));
    } else {
        int32_t ys = yearStart(UMALQURA_YEAR_START-1);
        ys+= handleGetYearLength(UMALQURA_YEAR_START-1);
        for(int i=UMALQURA_YEAR_START; i< year; i++){
            ys+= handleGetYearLength(i);
        }
        return ys;
    }
}
