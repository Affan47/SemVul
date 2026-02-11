show_stmt_wait(ivl_statement_t net, unsigned ind)
{
      unsigned idx;
      const char*comma = "";
      fprintf(out, "%*s@(", ind, "");

      for (idx = 0 ;  idx < ivl_stmt_nevent(net) ;  idx += 1) {
	    ivl_event_t evnt = ivl_stmt_events(net, idx);

	    if (evnt == 0)
		  fprintf(out, "%s/*ERROR*/", comma);
	    else
		  fprintf(out, "%s%s.%s", comma,
			  ivl_scope_name(ivl_event_scope(evnt)),
			  ivl_event_basename(evnt));

	    comma = ", ";
      }

      fprintf(out, ")\n");
      show_statement(ivl_stmt_sub_stmt(net), ind+4);
}
