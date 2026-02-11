lto_tag_check (enum LTO_tags actual, enum LTO_tags expected)
{
  if (actual != expected)
    internal_error ("bytecode stream: expected tag %s instead of %s",
		    lto_tag_name (expected), lto_tag_name (actual));
}
