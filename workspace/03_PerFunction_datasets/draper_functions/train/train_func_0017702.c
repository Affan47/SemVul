prd_printer(const struct ltab *lt)
{
	mvaddstr(lt->row, lt->col, Displayopts.opt_restrp? Displayopts.opt_restrp: "");
}
