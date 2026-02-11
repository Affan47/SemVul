ydefine(RouterT *r, const String &fname, const String &ftype, bool isformal, const Lexeme &t, bool &scope_order_error)
{
    if (!r->define(fname, ftype, isformal))
	lerror(t, "parameter '$%s' multiply defined", fname.c_str());
    else if (isformal) {
	if (ftype)
	    for (int i = 0; i < r->scope().size() - 1; i++)
		if (r->scope().value(i) == ftype) {
		    lerror(t, "repeated keyword parameter '%s' in compound element", ftype.c_str());
		    break;
		}
	if (!scope_order_error && r->nformals() > 1
	    && ((!ftype && r->scope().value(r->nformals() - 2))
		|| r->scope().value(r->nformals() - 2) == "__REST__")) {
	    lerror(t, "compound element parameters out of order\n(The correct order is '[positional], [keywords], [__REST__]'.)");
	    scope_order_error = true;
	}
    }
}
