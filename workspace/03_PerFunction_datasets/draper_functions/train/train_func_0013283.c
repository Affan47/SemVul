ompcbe_write_selfinvalidate(csbe_context *cx, Operand *op)
{
    if (oscar_api_ver_major >= 2) {
	csbe_printf(cx, "#pragma oscar cache_selfinvalidate");
	if (op != NULL) {
	    csbe_printf(cx, " (");
	    csbe_write_operand(cx, op);

	    csbe_printf(cx, ", 1)");
	}
	csbe_printf(cx, "\n");
    } else {
	if (op == NULL) {
	    csbe_printf(cx, "drv_selfinvalidate_cache();\n");
	} else {

	    csbe_printf(cx, "ocbi(");
	    csbe_write_operand(cx, op);
	    csbe_printf(cx, ");\n");
	}
    }
}
