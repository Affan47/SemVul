final_prescan_insn (rtx insn, rtx *operand ATTRIBUTE_UNUSED,
		    int num_operands ATTRIBUTE_UNUSED)
{

  static int last_insn_address = 0;

  const int uid = INSN_UID (insn);

  if (TARGET_ADDRESSES)
    {
      fprintf (asm_out_file, "; 0x%x %d\n", INSN_ADDRESSES (uid),
	       INSN_ADDRESSES (uid) - last_insn_address);
      last_insn_address = INSN_ADDRESSES (uid);
    }
}
