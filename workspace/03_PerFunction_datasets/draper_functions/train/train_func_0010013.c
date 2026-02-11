nv_exmode(cap)
    cmdarg_T	*cap;
{


#ifdef FEAT_VISUAL
    if (VIsual_active)
	vim_beep();
    else
#endif
	if (!checkclearop(cap->oap))
	do_exmode(FALSE);
}
