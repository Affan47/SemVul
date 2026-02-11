postscript_format() {
    return ((ExportChooserImpl*)impl_)->_obse
	? strncmp(((ExportChooserImpl*)impl_)->_obse->labelvalue().string(), "idraw", 5) == 0  || strcasecmp(((ExportChooserImpl*)impl_)->_obse->labelvalue().string(), "EPS") == 0
	: false;
}
