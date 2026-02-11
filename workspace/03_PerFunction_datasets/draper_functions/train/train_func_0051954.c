r300_vertex_program_dump(struct radeon_compiler *compiler, void *user)
{
	struct r300_vertex_program_compiler *c = (struct r300_vertex_program_compiler*)compiler;
	struct r300_vertex_program_code * vs = c->code;
	unsigned instrcount = vs->length / 4;
	unsigned i;

	fprintf(stderr, "Final vertex program code:\n");

	for(i = 0; i < instrcount; i++) {
		unsigned offset = i*4;
		unsigned src;

		fprintf(stderr, "%d: op: 0x%08x", i, vs->body.d[offset]);
		r300_vs_op_dump(vs->body.d[offset]);

		for(src = 0; src < 3; ++src) {
			fprintf(stderr, " src%i: 0x%08x", src, vs->body.d[offset+1+src]);
			r300_vs_src_dump(vs->body.d[offset+1+src]);
		}
	}

	fprintf(stderr, "Flow Control Ops: 0x%08x\n",vs->fc_ops);
	for(i = 0; i < vs->num_fc_ops; i++) {
		unsigned is_loop = 0;
		switch((vs->fc_ops >> (i * 2)) & 0x3 ) {
		case 0: fprintf(stderr, "NOP"); break;
		case 1: fprintf(stderr, "JUMP"); break;
		case 2: fprintf(stderr, "LOOP"); is_loop = 1; break;
		case 3: fprintf(stderr, "JSR"); break;
		}
		if (c->Base.is_r500) {
			fprintf(stderr,": uw-> 0x%08x lw-> 0x%08x "
							"loop data->0x%08x\n",
				vs->fc_op_addrs.r500[i].uw,
				vs->fc_op_addrs.r500[i].lw,
				vs->fc_loop_index[i]);
			if (is_loop) {
				fprintf(stderr, "Before = %u First = %u Last = %u\n",
					vs->fc_op_addrs.r500[i].lw & 0xffff,
					(vs->fc_op_addrs.r500[i].uw >> 16) & 0xffff,
					vs->fc_op_addrs.r500[i].uw  & 0xffff);
			}
		} else {
			fprintf(stderr,": 0x%08x\n", vs->fc_op_addrs.r300[i]);
		}
	}
}
