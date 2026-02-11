alloc(CVmGramProdMem *mem, size_t tok_pos,
                                   const vm_val_t *tok_match_result,
                                   int matched_star,
                                   vm_prop_id_t target_prop,
                                   vm_obj_id_t proc_obj,
                                   const CVmGramProdMatch **sub_match_list,
                                   size_t sub_match_cnt)
    {
        CVmGramProdMatch *match;


        match = (CVmGramProdMatch *)mem->alloc(sizeof(CVmGramProdMatch));


        match->tok_pos_ = tok_pos;
        match->matched_star_ = matched_star;
        match->target_prop_ = target_prop;
        match->proc_obj_ = proc_obj;
        match->sub_match_list_ = sub_match_list;
        match->sub_match_cnt_ = sub_match_cnt;


        if (tok_match_result != 0)
            match->tok_match_result_ = *tok_match_result;
        else
            match->tok_match_result_.set_nil();


        return match;
    }
