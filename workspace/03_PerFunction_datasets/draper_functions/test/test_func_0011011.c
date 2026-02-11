internal_maximal_insn_latency (int insn_code ATTRIBUTE_UNUSED,
	rtx insn ATTRIBUTE_UNUSED)
{
  switch (insn_code)
    {
    }
  return default_latencies[insn_code];
}
