i915_ring_seqno_info(struct seq_file *m,
				 struct intel_engine_cs *ring)
{
	if (ring->get_seqno) {
		seq_printf(m, "Current sequence (%s): %x\n",
			   ring->name, ring->get_seqno(ring, false));
	}
}
