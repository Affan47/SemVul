goto_tabpage_tp(tp)
    tabpage_T	*tp;
{
    if (tp != curtab && leave_tabpage(tp->tp_curwin->w_buffer) == OK)
    {
	if (valid_tabpage(tp))
	    enter_tabpage(tp, curbuf);
	else
	    enter_tabpage(curtab, curbuf);
    }
}
