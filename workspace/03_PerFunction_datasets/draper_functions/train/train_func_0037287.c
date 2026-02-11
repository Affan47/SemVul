asm_emit_property(void *e, struct label *labels)
{
	FILE *f = e;
	struct label *l;

	for_each_label(labels, l) {
		fprintf(f, "\t.globl\t%s\n", l->label);
		fprintf(f, "%s:\n", l->label);
	}
	fprintf(f, "\t/* FDT_PROP */\n");
	asm_emit_cell(e, FDT_PROP);
}
