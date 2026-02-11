emit_label_after (rtx label, rtx after)
{


  if (INSN_UID (label) == 0)
    {
      INSN_UID (label) = cur_insn_uid++;
      add_insn_after (label, after);
    }

  return label;
}
