list_op(char *arg, char *cp)
{
	int	cnt;

	*cp = '\0';

	for  (cnt = 0;  cnt < sizeof(aolist) / sizeof(struct argop);  cnt++)  {
		struct  argop  *aop = &aolist[cnt];
		if  (ncstrcmp(aop->name, arg) == 0)  {
			*cp++ = '=';
			switch  (aop->typ)  {
			case  AO_BOOL:
				switch  (*cp)  {
				case  'y':case  'Y':
				case  't':case  'T':
					aop->off = 0;
					break;
				case  'n':case  'N':
				case  'f':case  'F':
					aop->off = 255;
					break;
				default:
					goto  badarg;
				}
				break;
			case  AO_ULONG:
				if  (!isdigit(*cp))
					goto  badarg;
				aop->ao_un.ao_ulong = strtoul(cp, (char **) 0, 0);
				break;
			case  AO_STRING:
				aop->ao_un.ao_string = cp;
				break;
			}
			if  (!aop->had)  {
				aop->had = 1;
				aop->next = aochain;
				aochain = aop;
			}
			return;
		}
	}

	*cp++ = '=';
 badarg:
	if  (html_out_cparam_file("badcarg", 1, arg))
		exit(E_USAGE);
	html_error(arg);
	exit(E_SETUP);
}
