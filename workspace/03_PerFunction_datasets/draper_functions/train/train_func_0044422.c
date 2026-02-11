pro_class(const struct ltab *lt)
{
	classcode_t	in;
	struct	sctrl	wht_cl;

	wht_cl.helpcode = lt->helpcode * 10;
	wht_cl.helpfn = HELPLESS;
	wht_cl.size = lt->size;
	wht_cl.col = lt->col;
	wht_cl.magic_p = MAG_P|MAG_R;
	wht_cl.min = 1L;
	wht_cl.vmax = LOTSANDLOTS;
	wht_cl.msg = (char *) 0;

	in = whexnum(stdscr, lt->row, &wht_cl, Displayopts.opt_classcode);
	reset_state();
	if  (in == Displayopts.opt_classcode  &&  wht_cl.retv == 405)
		return  wht_cl.retv;

	if  (!(mypriv->spu_flgs & PV_COVER))
		in &= mypriv->spu_class;

	if  (in == 0L)  {
		mvaddstr(lt->row, lt->col, hex_disp(Displayopts.opt_classcode, 1));
		disp_str = hex_disp(mypriv->spu_class, 0);
		doerror(stdscr, 757);
		return  0;
	}

	Displayopts.opt_classcode = in;
	hadrfresh++;
	Job_seg.Last_ser = 0;
	Ptr_seg.Last_ser = 0;
	return  wht_cl.retv? wht_cl.retv: 404;
}
