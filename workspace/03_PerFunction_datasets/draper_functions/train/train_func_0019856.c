execute( Chuck_VM * vm, Chuck_VM_Shred * shred )
{

    switch (m_type_ref->xid) {
    case te_int:
    case te_uint:
    {
        t_CKINT * sp = (t_CKINT *)shred->reg->sp;

	fprintf( stderr, "%d :(%s)\n", *(sp-1), m_type_ref->c_name() );
	break;
    }
    case te_string:
    {
        t_CKINT * sp = (t_CKINT *)shred->reg->sp;

        fprintf( stderr, "\"%s\" : (%s)\n", ((Chuck_String *)*(sp-1))->str.c_str(), m_type_ref->c_name() );
	break;
    }
    case te_single:
    case te_float:
    case te_double:
    case te_time:
    case te_dur:
    {
        t_CKFLOAT * sp = (t_CKFLOAT *)shred->reg->sp;

        fprintf( stderr, "%f :(%s)\n", *(sp-1), m_type_ref->c_name() );
	break;
    }
    default:
        fprintf( stderr, "... :(%s)\n", m_type_ref->c_name() );
	break;
    }


    fflush( stderr );
}
