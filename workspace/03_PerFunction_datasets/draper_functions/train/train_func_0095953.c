fsbe_write_pe_statement(cx, sp)
fsbe_context *cx;
Pe_statement *sp;
{
  Statement *p;

  fsbe_begin_pe_statement(cx, sp);

  for (p = sp->stm_head; p; p = p->next)
    if (!fsbe_write_pe_statement_item_hook(cx, sp, p)) {
      FSBE_HOOKDECL(int
		    fsbe_write_pe_statement_item_hook(cx, sp, p)
		    fsbe_context *cx;
		    Pe_statement *sp;
		    Statement *p;
		    );
      fsbe_write_statement(cx, p);
    }

  fsbe_end_pe_statement(cx, sp);
}
