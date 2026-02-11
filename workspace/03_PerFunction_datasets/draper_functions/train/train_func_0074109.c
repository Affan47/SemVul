get_module(void *vcx)
{
    Module_table *mp;

    switch(out_lang_tag) {
    case LANG_FORTRAN:
        mp = ((fsbe_context *)vcx)->module;
        break;
    case LANG_C:
        mp = ((csbe_context *)vcx)->module;
        break;
    default:
	mp = NULL;
	fatal("unexpected language\n");
	break;
    }

    return mp;
}
