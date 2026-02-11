parse_panic(struct vcc *tl)
{
	vcc_NextToken(tl);

	Fb(tl, 1, "VRT_panic(sp, ");
	vcc_Expr(tl, STRING);
	ERRCHK(tl);
	Fb(tl, 0, ", vrt_magic_string_end);\n");
}
