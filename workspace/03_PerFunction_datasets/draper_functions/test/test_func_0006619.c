load_glas(struct bc_read_stream *s, struct grammar *g)
{

    g->num_glas = 0;
    while(1)
    {
        struct record_info ri = bc_rs_next_data_record(s);
        if(ri.record_type == StartBlock && ri.id == BC_GLA)
        {
            g->num_glas++;
            bc_rs_skip_block(s);
        }
        else if(ri.record_type == EndBlock)
            break;
        else
            unexpected(s, ri);
    }

    bc_rs_rewind_block(s);
    g->glas = malloc(g->num_glas * sizeof(*g->glas));
    int gla_offset = 0;

    while(1)
    {
        struct record_info ri = bc_rs_next_data_record(s);
        if(ri.record_type == StartBlock && ri.id == BC_GLA)
        {
            load_gla(s, &g->glas[gla_offset++], g);
        }
        else if(ri.record_type == EndBlock)
            break;
        else
            unexpected(s, ri);
    }
}
