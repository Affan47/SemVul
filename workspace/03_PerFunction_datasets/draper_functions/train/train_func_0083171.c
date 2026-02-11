att_distance (long int i, long int j)


{
    double xd = instance.nodeptr[i].x - instance.nodeptr[j].x;
    double yd = instance.nodeptr[i].y - instance.nodeptr[j].y;
    double rij = sqrt ((xd * xd + yd * yd) / 10.0);
    double tij = dtrunc (rij);
    long int dij;

    if (tij < rij)
        dij = (int) tij + 1;
    else
        dij = (int) tij;
    return dij;
}
