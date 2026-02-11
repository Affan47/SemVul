rel_type(unsigned type)
{
	static const char *type_name[] = {
#define REL_TYPE(X) [X] = #X
		REL_TYPE(R_386_NONE),
		REL_TYPE(R_386_32),
		REL_TYPE(R_386_PC32),
		REL_TYPE(R_386_GOT32),
		REL_TYPE(R_386_PLT32),
		REL_TYPE(R_386_COPY),
		REL_TYPE(R_386_GLOB_DAT),
		REL_TYPE(R_386_JMP_SLOT),
		REL_TYPE(R_386_RELATIVE),
		REL_TYPE(R_386_GOTOFF),
		REL_TYPE(R_386_GOTPC),
		REL_TYPE(R_386_8),
		REL_TYPE(R_386_PC8),
		REL_TYPE(R_386_16),
		REL_TYPE(R_386_PC16),
#undef REL_TYPE
	};
	const char *name = "unknown type rel type name";
	if (type < ARRAY_SIZE(type_name) && type_name[type]) {
		name = type_name[type];
	}
	return name;
}
