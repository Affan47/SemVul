Split(const int xp ,
                                           const int yp ,
                                           const int xl ,
                                           const int yl ,
                                           CoeffArray& coeff_data)
{
    const int xend=xp+xl;
    const int yend=yp+yl;

    CoeffType* line_data;


    for (int j = yp; j < yend; ++j)
    {
        line_data = &(coeff_data[j][xp]);
        ShiftRowLeft(line_data, xl, 1);
        for (int i = xp+1; i < xend; i+=2)
        {


            coeff_data[j][i] -= coeff_data[j][i-1];


            coeff_data[j][i-1] += ((coeff_data[j][i]+1)>>1);
        }
    }


    for (int j = yp+1; j < yend; j+=2)
    {
        for (int i = xp; i < xend; ++i)
        {
            coeff_data[j][i] -= coeff_data[j-1][i];
            coeff_data[j-1][i] += ((coeff_data[j][i]+1)>>1);
        }
    }


    DeInterleave( xp , yp , xl , yl , coeff_data );
}
