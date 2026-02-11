odometermore(Odometer* odom)
{
    return (odom->rank > 0
            && odom->index[0] < (odom->start[0]+odom->count[0]));
}
