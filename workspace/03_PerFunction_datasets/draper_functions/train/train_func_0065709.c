init_gcc_specs (struct obstack *obstack, const char *shared_name,
		const char *static_name, const char *eh_name)
{
  char *buf;

  buf = concat ("%{static|static-libgcc:", static_name, " ", eh_name, "}"
		"%{!static:%{!static-libgcc:"
#if USE_LD_AS_NEEDED
		"%{!shared-libgcc:",
		static_name, " --as-needed ", shared_name, " --no-as-needed"
		"}"
		"%{shared-libgcc:",
		shared_name, "%{!shared: ", static_name, "}"
		"}"
#else
		"%{!shared:"
		"%{!shared-libgcc:", static_name, " ", eh_name, "}"
		"%{shared-libgcc:", shared_name, " ", static_name, "}"
		"}"
#ifdef LINK_EH_SPEC
		"%{shared:"
		"%{shared-libgcc:", shared_name, "}"
		"%{!shared-libgcc:", static_name, "}"
		"}"
#else
		"%{shared:", shared_name, "}"
#endif
#endif
		"}}", NULL);

  obstack_grow (obstack, buf, strlen (buf));
  free (buf);
}
