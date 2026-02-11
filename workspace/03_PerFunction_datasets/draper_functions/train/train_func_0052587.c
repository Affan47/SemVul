sbe_str_qr_operator( fsbe_context *cx, qr_operator ope )
{
    switch( out_lang_tag ){
    case LANG_FORTRAN:
	return fsbe_str_qr_operator( cx, ope );
	break;
    default:
	break;
    }
    return NULL;
}
