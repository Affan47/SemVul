make_replace(ast_field* src) {
        if (INFO.tgt_scalar)
            return make_replace_field(src);
        else
            return make_replace_id(src);
    }
