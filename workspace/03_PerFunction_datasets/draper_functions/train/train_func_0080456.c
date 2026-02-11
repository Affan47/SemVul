aarch64_emit_store_exclusive (enum machine_mode mode, rtx bval,
			      rtx rval, rtx mem, rtx model_rtx)
{
  rtx (*gen) (rtx, rtx, rtx, rtx);

  switch (mode)
    {
    case QImode: gen = gen_aarch64_store_exclusiveqi; break;
    case HImode: gen = gen_aarch64_store_exclusivehi; break;
    case SImode: gen = gen_aarch64_store_exclusivesi; break;
    case DImode: gen = gen_aarch64_store_exclusivedi; break;
    default:
      gcc_unreachable ();
    }

  emit_insn (gen (bval, rval, mem, model_rtx));
}
