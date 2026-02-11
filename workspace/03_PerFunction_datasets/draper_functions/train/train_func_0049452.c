textformat_color(const fn_call& fn)
{
    TextFormat_as* relay = ensure<ThisIsNative<TextFormat_as> >(fn);

	as_value ret;

	if (fn.nargs == 0) {
		if (relay->color()) ret.set_double(relay->color()->toRGB());
		else ret.set_null();
	}
	else {
		rgba newcolor;
		newcolor.parseRGB(toInt(fn.arg(0), getVM(fn)));
		relay->colorSet(newcolor);
	}

	return ret;
}
