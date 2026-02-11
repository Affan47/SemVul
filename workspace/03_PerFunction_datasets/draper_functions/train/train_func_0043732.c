display_med_capability(struct writer *w, long int available, int cap,
    const char *symbol)
{
	if (available & cap) {
		tag_start(w, "capability", "Capability");
		tag_attr(w, "type", "", symbol);
		tag_end(w);
	}
}
