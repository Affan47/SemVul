vlan_print_flags(FILE *fp, __u32 flags)
{
	fprintf(fp, "<");
#define _PF(f)	if (flags & VLAN_FLAG_##f) { \
			flags &= ~ VLAN_FLAG_##f; \
			fprintf(fp, #f "%s", flags ? "," : ""); \
		}
	_PF(REORDER_HDR);
	_PF(GVRP);
	_PF(MVRP);
	_PF(LOOSE_BINDING);
#undef _PF
	if (flags)
		fprintf(fp, "%x", flags);
	fprintf(fp, "> ");
}
