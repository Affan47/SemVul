compile(){
    if (compiled){
        return 0;
    }
    compiled = 1;
    int in_pos;
    soft_remap_tab = new int[in_length];

    int last_mapped_position_source = 0;
    int last_mapped_position_dest = 0;
    for (in_pos=0;in_pos<in_length;in_pos++){
        soft_remap_tab[in_pos] = -1;
    }

    for (in_pos=0;in_pos<in_length;in_pos++){
        int new_dest;

        if ((new_dest = remap_tab[in_pos]) <0){
            continue;
        }
        {
            int source;
            int dest;
            int dsource = in_pos - last_mapped_position_source;
            int ddest = new_dest - last_mapped_position_dest;

            for (source = last_mapped_position_source, dest = last_mapped_position_dest;
                 source <= last_mapped_position_source + (dsource>1) &&
                     dest <= last_mapped_position_dest + (ddest>1);
                 source++,dest++){
                soft_remap_tab[source] = dest;
            }
            for (source = in_pos, dest = new_dest;
                 source > last_mapped_position_source + (dsource>1) &&
                     dest > last_mapped_position_dest + (ddest>1);
                 source--,dest--){
                soft_remap_tab[source] = dest;
            }
        }
        last_mapped_position_source = in_pos;
        last_mapped_position_dest = new_dest;
    }
    return 0;
}
