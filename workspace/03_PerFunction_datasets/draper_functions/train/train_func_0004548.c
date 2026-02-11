init_registry()
{
	REGISTER(ATOM_HT_REGISTRY, ht_registry);
	REGISTER(ATOM_HT_REGISTRY_NODE, ht_registry_node);
	REGISTER(ATOM_HT_REGISTRY_DATA_STREE, ht_registry_data_stree);
	REGISTER(ATOM_HT_REGISTRY_DATA_DWORD, ht_registry_data_dword);
	REGISTER(ATOM_HT_REGISTRY_DATA_RAW, ht_registry_data_raw);
	REGISTER(ATOM_HT_REGISTRY_DATA_STRING, ht_registry_data_string);
	REGISTER(ATOM_HT_REGISTRY_NODE_TYPE_DESC, ht_registry_node_type_desc);

	registerAtom(ATOM_HT_CREATE_EMPTY_SYMLINK, (void*)create_empty_symlink);
	registerAtom(ATOM_HT_CREATE_EMPTY_DWORD, (void*)create_empty_dword);
	registerAtom(ATOM_HT_CREATE_EMPTY_STRING, (void*)create_empty_string);
	registerAtom(ATOM_HT_CREATE_EMPTY_RAW, (void*)create_empty_raw);


#if ! GENERATE_NEW_REGISTRY
	ConstMemMapFile f(default_reg, sizeof default_reg);
	CompressedStream c(&f, false);
	ObjectStreamBin o(&c, false);

	GET_OBJECT(o, registry);
#else
	registry = new ht_registry;
	registry->init();

	LocalFile f("ht.reg", IOAM_WRITE, FOM_CREATE);
	CompressedStream c(&f, false);
	ObjectStreamBin o(&c, false);

	PUT_OBJECT(o, registry);
#endif

	return true;
}
