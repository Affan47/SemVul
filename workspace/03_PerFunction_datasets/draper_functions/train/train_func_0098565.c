resizeWhichGenerator(int numberNow, int numberAfter)
{
    if (numberAfter > maximumWhich_) {
        maximumWhich_ = CoinMax(maximumWhich_ * 2 + 100, numberAfter) ;
        int * temp = new int[2*maximumWhich_] ;
        memcpy(temp, whichGenerator_, numberNow*sizeof(int)) ;
        delete [] whichGenerator_ ;
        whichGenerator_ = temp ;
        memset(whichGenerator_ + numberNow, 0, (maximumWhich_ - numberNow)*sizeof(int));
    }
}
