csr1212_generate_tree_subdir(struct csr1212_keyval *dir,
					 u_int32_t *data_buffer)
{
	struct csr1212_dentry *dentry;
	struct csr1212_keyval *last_extkey_spec = NULL;
	struct csr1212_keyval *last_extkey = NULL;
	int index = 0;

	for (dentry = dir->value.directory.dentries_head; dentry; dentry = dentry->next) {
		struct csr1212_keyval *a;

		for (a = dentry->kv; a; a = a->associate) {
			u_int32_t value = 0;


			if (a->key.id == CSR1212_KV_ID_EXTENDED_KEY_SPECIFIER_ID) {
				if (last_extkey_spec == NULL) {
					last_extkey_spec = a;
				} else if (a->value.immediate != last_extkey_spec->value.immediate) {
					last_extkey_spec = a;
				} else {
					continue;
				}

			} else if (a->key.id == CSR1212_KV_ID_EXTENDED_KEY) {
				if (last_extkey == NULL) {
					last_extkey = a;
				} else if (a->value.immediate != last_extkey->value.immediate) {
					last_extkey = a;
				} else {
					continue;
				}
			}

			switch(a->key.type) {
			case CSR1212_KV_TYPE_IMMEDIATE:
				value = a->value.immediate;
				break;
			case CSR1212_KV_TYPE_CSR_OFFSET:
				value = a->value.csr_offset;
				break;
			case CSR1212_KV_TYPE_LEAF:
				value = a->offset;
				value -= dir->offset + quads_to_bytes(1+index);
				value = bytes_to_quads(value);
				break;
			case CSR1212_KV_TYPE_DIRECTORY:
				value = a->offset;
				value -= dir->offset + quads_to_bytes(1+index);
				value = bytes_to_quads(value);
				break;
			default:

				break;
			}

			value |= (a->key.id & CSR1212_KV_KEY_ID_MASK) << CSR1212_KV_KEY_SHIFT;
			value |= (a->key.type & CSR1212_KV_KEY_TYPE_MASK) <<
				(CSR1212_KV_KEY_SHIFT + CSR1212_KV_KEY_TYPE_SHIFT);
			data_buffer[index] = CSR1212_CPU_TO_BE32(value);
			index++;
		}
	}
}
