symbol_eval(eval_scalar *r, char *symbol)
{
	if (strcmp(symbol, "_") == 0) {
		if (have_last_result) {
			 scalar_clone(r, &last_result);
			 return true;
		} else {
			set_eval_error("no previous result...");
			return false;
		}
	}
	return real_symbol_handler ? real_symbol_handler(r, symbol) : false;
}
