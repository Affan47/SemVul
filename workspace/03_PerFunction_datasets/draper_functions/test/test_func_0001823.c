inc_id(){
    unsigned short ret=net_current_id++;

    if ( net_current_id > net_max_current_id )
    {
        net_current_id = 1;
    }

    if (net_current_id==0)
        net_current_id++;
    return ret;
}
