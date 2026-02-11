fs_hash_init(fsp_hash_enum type)
{
    switch (type) {
    case FS_HASH_MD5:
    case FS_HASH_CRC64:
	fs_error(LOG_CRIT, "Unsuported backend hash function, exiting");
	exit(4);
	break;
    case FS_HASH_UMAC:
	break;
    case FS_HASH_UNKNOWN:
	fs_error(LOG_CRIT, "Unknown backend hash function, exiting");
	exit(4);
	break;
    }

    bnids = g_hash_table_new_full(g_str_hash, g_str_equal, bnhash_destroy,
	    NULL);

    atexit(fs_hash_fini);

    fs_c.empty = 0LL;
    fs_c.xsd_string = fs_hash_uri(XSD_STRING);
    fs_c.xsd_integer = fs_hash_uri(XSD_INTEGER);
    fs_c.xsd_float = fs_hash_uri(XSD_FLOAT);
    fs_c.xsd_double = fs_hash_uri(XSD_DOUBLE);
    fs_c.xsd_decimal = fs_hash_uri(XSD_DECIMAL);
    fs_c.xsd_boolean = fs_hash_uri(XSD_BOOLEAN);
    fs_c.xsd_datetime = fs_hash_uri(XSD_DATETIME);
    fs_c.xsd_pinteger = fs_hash_uri(XSD_NAMESPACE "positiveInteger");
    fs_c.xsd_ninteger = fs_hash_uri(XSD_NAMESPACE "negativeInteger");
    fs_c.xsd_npinteger = fs_hash_uri(XSD_NAMESPACE "nonPositiveInteger");
    fs_c.xsd_nninteger = fs_hash_uri(XSD_NAMESPACE "nonNegativeInteger");
    fs_c.xsd_long = fs_hash_uri(XSD_NAMESPACE "long");
    fs_c.xsd_int = fs_hash_uri(XSD_NAMESPACE "int");
    fs_c.xsd_short = fs_hash_uri(XSD_NAMESPACE "short");
    fs_c.xsd_byte = fs_hash_uri(XSD_NAMESPACE "byte");
    fs_c.xsd_ulong = fs_hash_uri(XSD_NAMESPACE "unsignedLong");
    fs_c.xsd_uint = fs_hash_uri(XSD_NAMESPACE "unsignedInt");
    fs_c.xsd_ushort = fs_hash_uri(XSD_NAMESPACE "unsignedShort");
    fs_c.xsd_ubyte = fs_hash_uri(XSD_NAMESPACE "unsignedByte");
    fs_c.lang_en = fs_hash_literal("en", 0);
    fs_c.lang_fr = fs_hash_literal("fr", 0);
    fs_c.lang_de = fs_hash_literal("de", 0);
    fs_c.lang_es = fs_hash_literal("es", 0);
    fs_c.rdf_type = fs_hash_uri(RDF_NAMESPACE "type");
    fs_c.default_graph = fs_hash_uri(FS_DEFAULT_GRAPH);
    fs_c.system_config = fs_hash_uri(FS_SYSTEM_CONFIG);
    fs_c.rdfs_label = fs_hash_uri(RDFS_LABEL);
    fs_c.fs_text_index = fs_hash_uri(FS_TEXT_INDEX);
    fs_c.fs_token = fs_hash_uri(FS_TEXT_TOKEN);
    fs_c.fs_dmetaphone = fs_hash_uri(FS_TEXT_DMETAPHONE);
    fs_c.fs_stem = fs_hash_uri(FS_TEXT_STEM);
}
