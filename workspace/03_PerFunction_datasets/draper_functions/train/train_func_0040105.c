call (Closure *closure, std::vector<Value> &args) {
    Operand tmp ;
    Value thisptr ((Object*)NULL) ;
    vm->randomCall (&tmp, dynamic_cast<Function*>(closure->block), closure->slink->frame, closure->slink, thisptr, args, true) ;
    return tmp.val ;
}
