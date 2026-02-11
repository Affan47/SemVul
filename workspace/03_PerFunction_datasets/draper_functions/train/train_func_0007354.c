csbe_begin_post_head(cx, bp)
csbe_context *cx;
Block *bp;
{
    Boolean is_1rot_loop;
    Quadruple *do_qr;
#ifdef CSBE_DEBUG
  if (bp->post_head) {
    csbe_printf(cx, "C *** >>> post_head\n");
  }
#endif

  if (is_do_loop(bp) && !has_apv_loop(bp)) {
      is_1rot_loop = block_is_1rot_loop(bp);
      do_qr = search_do_qr(bp);
      if (is_1rot_loop) {
	  csbe_printf(cx, "    ");
	  csbe_write_operand(cx, do_qr->op[0]);
	  csbe_printf(cx, " += ");
	  if( do_qr->op[3]->kind == KIND_TEMP )
	      csbe_printf(cx, "(");
	  csbe_write_operand(cx, do_qr->op[3]);
	  if( do_qr->op[3]->kind == KIND_TEMP )
	      csbe_printf(cx, ")");
	  csbe_printf(cx, ";\n");
      }
      else {
	  csbe_printf(cx, "      }\n");
      }
  }
}
