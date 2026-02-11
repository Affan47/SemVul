explainnewintelcacheinfo(unsigned long eax, unsigned long ebx,
                         unsigned long ecx, unsigned long edx)
{
	outputatlvl(1, "    * Level %lu ", ((eax >>  5) & 0x07));
	switch ((eax & 0x1f)) {
		case 1: outputatlvl(1, "%s", "Data Cache"); break;
		case 2: outputatlvl(1, "%s", "Instruction Cache"); break;
		case 3: outputatlvl(1, "%s", "Unified Cache"); break;
		default: outputatlvl(1, "[Unknown Cache Type %lu]", eax & 0x1f); break;
	};
	outputatlvl(1, ": %sself initializing, %sfully associative\n",
		    ((eax & 0x100) ? "" : "not "),
		    ((eax & 0x200) ? "" : "not "));
	outputatlvl(1, "    *  Shared by no more than %lu thread%s"
	               " of the %lu core%s in the package.\n",
		    ((eax >> 14) & 0x7ff) + 1,
		    ((((eax >> 14) & 0x7ff) == 0) ? "" : "s"),
		    ((eax >> 26) & 0x3f) + 1,
		    ((((eax >> 26) & 0x3f) == 0) ? "" : "s"));
}
