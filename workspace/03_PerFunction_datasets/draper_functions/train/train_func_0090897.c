gen_insn_reserv (rtx def)
{
  decl_t decl;

  decl = XCREATENODE (struct decl);
  decl->mode = dm_insn_reserv;
  decl->pos = 0;
  DECL_INSN_RESERV (decl)->name
    = check_name (XSTR (def, 0), decl->pos);
  DECL_INSN_RESERV (decl)->default_latency = XINT (def, 1);
  DECL_INSN_RESERV (decl)->condexp = XEXP (def, 2);
  DECL_INSN_RESERV (decl)->regexp = gen_regexp (XSTR (def, 3));
  decls.safe_push (decl);
}
