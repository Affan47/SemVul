command_opts(optkey)
int optkey;
{
   struct opt_list * ol;
   for(ol=options; ol; ol=ol->next)
      if (ol->opttype == optkey)
	 command_opt(ol->opt);
}
