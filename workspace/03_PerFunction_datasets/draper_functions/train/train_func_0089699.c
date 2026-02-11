apply(ast_sent* s) {
        if(s->get_nodetype() != AST_ASSIGN) return true;

        ast_assign* assign = (ast_assign*) s;
        if(!assign->is_target_scalar()) return true;

        gm_symtab_entry* target = assign->get_lhs_scala()->getSymInfo();
        if(!gm_is_sequence_collection_type(target->getType()->getTypeSummary())) return true;

        ast_expr* rhs = assign->get_rhs();
        if(!rhs->is_id()) return true;

        ast_id* rhs_id = rhs->get_id();
        if(!gm_is_collection_iterator_type(rhs_id->getTypeSummary())) return true;

        Iterator position = std::find(candidates.begin(), candidates.end(), target);
        if (position != candidates.end()) candidates.erase(position);

        return true;
    }
