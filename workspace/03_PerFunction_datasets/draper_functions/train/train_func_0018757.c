finish(StringAccum &source, const StringAccum &program, int used)
{
    if (used & used_mach)
	source << "  const uint32_t *mach_data = reinterpret_cast<const uint32_t *>(p->mac_header() - 2);\n";
    if (used & used_neth)
	source << "  const uint32_t *neth_data = reinterpret_cast<const uint32_t *>(p->network_header());\n";
    if (used & used_transph)
	source << "  const uint32_t *transph_data = reinterpret_cast<const uint32_t *>(p->transport_header());\n";
    source << program;
}
