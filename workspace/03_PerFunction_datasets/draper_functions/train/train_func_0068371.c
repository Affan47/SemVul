ls_encode_run(JLSState *state, PutBitContext *pb, int run, int comp, int trail){
    while(run >= (1 << ff_log2_run[state->run_index[comp]])){
        put_bits(pb, 1, 1);
        run -= 1 << ff_log2_run[state->run_index[comp]];
        if(state->run_index[comp] < 31)
            state->run_index[comp]++;
    }

    if(!trail && run) {
        put_bits(pb, 1, 1);
    }else if(trail){
        put_bits(pb, 1, 0);
        if(ff_log2_run[state->run_index[comp]])
            put_bits(pb, ff_log2_run[state->run_index[comp]], run);
    }
}
