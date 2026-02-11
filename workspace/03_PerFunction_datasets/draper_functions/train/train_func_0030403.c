applyBuiltIn(ast_expr_builtin* builtIn, Iterator position, gm_builtin_def* def, gm_method_id_t methodId) {
        switch (methodId) {
            case GM_BLTIN_SET_ADD:
            case GM_BLTIN_SEQ_POP_FRONT:
            case GM_BLTIN_SET_PEEK:
            candidates.erase(position);
            break;
        }
    }
