CPRO_confidinterval(long res,long column,unsigned char which_statistic,char mode)
{
    STATTYPE hits=0, sum=0, group=0, different=0;
    long base=3*res;

    if(!(CPRO.result[which_statistic].statistic[base+0])) hits=0;
    else hits=CPRO.result[which_statistic].statistic[base+0][column];

    if(!(CPRO.result[which_statistic].statistic[base+1])) group=0;
    else group=CPRO.result[which_statistic].statistic[base+1][column];

    if(!(CPRO.result[which_statistic].statistic[base+2])) different=0;
    else different=CPRO.result[which_statistic].statistic[base+2][column];

    sum=hits+group+different;
    if(!(mode)) return(1/sqrt((float)sum)/2.0);
    else return(0.0);
}
