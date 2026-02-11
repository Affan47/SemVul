_gda_sqlite_compute_types_hash (SqliteConnectionData *cdata)
{
	if (!cdata->types_hash) {
		gint i;
		GType type, *array;
		GHashTable *hash;
		cdata->types_hash = g_hash_table_new (nocase_str_hash, nocase_str_equal);
		hash = cdata->types_hash;
#define NB_DECLARED_G_TYPES 14
		cdata->types_array = g_new (GType, NB_DECLARED_G_TYPES);
		array = cdata->types_array;

		type = G_TYPE_INT;
		i = 0;
		array [i] = type;
		g_hash_table_insert (hash, "integer", array + i);
		g_hash_table_insert (hash, "int", array + i);

		type = G_TYPE_UINT;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "unsigned integer", array + i);
		g_hash_table_insert (hash, "unsigned int", array + i);
		g_hash_table_insert (hash, "uint", array + i);

		type = G_TYPE_BOOLEAN;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "boolean", array + i);

		type = G_TYPE_DATE;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "date", array + i);

		type = GDA_TYPE_TIME;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "time", array + i);

		type = GDA_TYPE_TIMESTAMP;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "timestamp", array + i);

		type = G_TYPE_DOUBLE;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "real", array + i);

		type = G_TYPE_STRING;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "text", array + i);
		g_hash_table_insert (hash, "string", array + i);
		g_hash_table_insert (hash, "varchar", array + i);

		type = GDA_TYPE_BINARY;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "binary", array + i);

		type = GDA_TYPE_BLOB;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "blob", array + i);

		type = G_TYPE_INT64;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "int64", array + i);

		type = G_TYPE_UINT64;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "uint64", array + i);

		type = GDA_TYPE_SHORT;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "short", array + i);

		type = GDA_TYPE_USHORT;
		i++;
		array [i] = type;
		g_hash_table_insert (hash, "ushort", array + i);
		g_hash_table_insert (hash, "unsigned short", array + i);
		g_assert (i < NB_DECLARED_G_TYPES);
	}
}
