syck_emitter_emit(int argc, VALUE *argv, VALUE self)
{
    VALUE oid, proc;
    SyckEmitter *emitter;
    struct emitter_xtra *bonus;
    SYMID symple;
    int level = FIX2INT(rb_ivar_get(self, s_level)) + 1;
    rb_ivar_set(self, s_level, INT2FIX(level));

    rb_scan_args(argc, argv, "1&", &oid, &proc);
    Data_Get_Struct(self, SyckEmitter, emitter);
    bonus = (struct emitter_xtra *)emitter->bonus;


    bonus->oid = oid;
    if ( !NIL_P( oid ) && RTEST( rb_funcall( bonus->data, s_haskey, 1, oid ) ) ) {
        symple = rb_hash_aref( bonus->data, oid );
    } else {
        symple = rb_funcall( proc, s_call, 1, rb_ivar_get( self, s_out ) );
    }
    syck_emitter_mark_node( emitter, (st_data_t)symple );


    level -= 1;
    rb_ivar_set(self, s_level, INT2FIX(level));
    if ( level == 0 )
    {
        syck_emit(emitter, (st_data_t)symple);
        syck_emitter_flush(emitter, 0);

        return bonus->port;
    }

    return symple;
}
