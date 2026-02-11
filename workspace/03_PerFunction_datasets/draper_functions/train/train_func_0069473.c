op_deref(int mode, Value * v) {
    if (mode == MODE_SKIP) return;
#if ENABLE_Symbols
    if (v->type_class != TYPE_CLASS_ARRAY && v->type_class != TYPE_CLASS_POINTER) {
        error(ERR_INV_EXPRESSION, "Array or pointer type expected");
    }
    if (v->type_class == TYPE_CLASS_POINTER) {
        v->address = (ContextAddress)to_uns(mode, v);
        v->remote = 1;
        v->constant = 0;
        v->value = NULL;
    }
    if (get_symbol_base_type(v->type, &v->type) < 0) {
        error(errno, "Cannot retrieve symbol type");
    }
    if (get_symbol_type_class(v->type, &v->type_class) < 0) {
        error(errno, "Cannot retrieve symbol type class");
    }
    if (get_symbol_size(v->type, &v->size) < 0) {
        error(errno, "Cannot retrieve symbol size");
    }
#else
    error(ERR_UNSUPPORTED, "Symbols service not available");
#endif
}
