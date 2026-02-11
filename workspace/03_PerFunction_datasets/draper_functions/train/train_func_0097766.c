distmat_checkambigProt(ajint t1, ajint t2)
{
    float n;

    n = (float)0.;

    if( !strchr("X",t1) && t1 == t2 )
	n = (float)1.0;
    else if(((strchr("B",t1) && strchr("DN",t2)) ||
              (strchr("B",t2) && strchr("DN",t1))) )
	n = (float)0.5;
    else if(((strchr("Z",t1) && strchr("EQ",t2)) ||
              (strchr("Z",t2) && strchr("EQ",t1))) )
	n = (float)0.5;
    else if(((strchr("J",t1) && strchr("IL",t2)) ||
              (strchr("J",t2) && strchr("IL",t1))) )
	n = (float)0.5;
    else if( strchr("X",t1) && strchr("X",t2) )
	n = (float)0.0025;
    else if( strchr("X",t1) || strchr("X",t2) )
	n = (float)0.05;

    return n;
}
