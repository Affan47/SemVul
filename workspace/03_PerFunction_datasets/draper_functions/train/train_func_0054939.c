isqrt(unsigned int num,unsigned int guess)
{
    unsigned int sqr;
    unsigned int oldguess=guess;
    if (num==0) return 0;
    if (num<4) return 1;

    for (;;)
    {

        sqr=((num/guess)+guess)/2;
        if (sqr==guess || sqr==oldguess)
        {
            if (sqr*sqr>num) sqr--;
            return sqr;
        }
        oldguess=guess;
        guess=sqr;
    }
}
