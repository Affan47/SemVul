dirfmt(Fmt *fmt)
{
	char buf[160];

	fdirconv(buf, buf+sizeof buf, va_arg(fmt->args, Dir*));
	return fmtstrcpy(fmt, buf);
}
