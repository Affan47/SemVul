clone(CVmGramProdMem *mem)
    {
        CVmGramProdState *new_state;
        CVmGramProdState *new_enclosing;


        new_enclosing = (enclosing_ != 0 ? enclosing_->clone(mem) : 0);


        new_state = alloc(mem, tok_pos_, alt_pos_, new_enclosing,
                          altp_, prod_obj_, circular_alt_);


        new_state->sub_target_prop_ = sub_target_prop_;


        if (alt_pos_ != 0)
            memcpy(new_state->match_list_, match_list_,
                   alt_pos_ * sizeof(match_list_[0]));


        new_state->nxt_ = 0;


        new_state->matched_star_ = matched_star_;


        return new_state;
    }
