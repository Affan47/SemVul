dump_gimple_debug (pretty_printer *buffer, gimple gs, int spc, int flags)
{
  switch (gs->gsbase.subcode)
    {
    case GIMPLE_DEBUG_BIND:
      if (flags & TDF_RAW)
	dump_gimple_fmt (buffer, spc, flags, "%G BIND <%T, %T>", gs,
			 gimple_debug_bind_get_var (gs),
			 gimple_debug_bind_get_value (gs));
      else
	dump_gimple_fmt (buffer, spc, flags, "# DEBUG %T => %T",
			 gimple_debug_bind_get_var (gs),
			 gimple_debug_bind_get_value (gs));
      break;

    default:
      gcc_unreachable ();
    }
}
