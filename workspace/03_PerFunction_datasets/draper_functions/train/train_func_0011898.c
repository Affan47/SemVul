mcnet_metadata_generator_write(mcnet_metadata_t* metadata, uint8_t* out) {
  size_t offset = 0;

  int i;
  for (i = 0; i < metadata->count; ++i) {
    out[offset] = ((metadata->entries[i]->type & 0x08) << 5) + (metadata->entries[i]->index & 0xe0);
    offset += 1;

    if (metadata->entries[i] == NULL) {
      return MCNET_EINVALID;
    }

    switch (metadata->entries[i]->type) {
      case MCNET_METADATA_TYPE_BYTE: {
        mcnet_metadata_entry_byte_t* _entry = (mcnet_metadata_entry_byte_t*)(metadata->entries[i]);
        out[offset] = _entry->data;
        offset += 1;
        break;
      }
      case MCNET_METADATA_TYPE_SHORT: {
        mcnet_metadata_entry_short_t* _entry = (mcnet_metadata_entry_short_t*)(metadata->entries[i]);
        mcnet_write_int16(out + offset, _entry->data);
        offset += 2;
        break;
      }
      case MCNET_METADATA_TYPE_INT: {
        mcnet_metadata_entry_int_t* _entry = (mcnet_metadata_entry_int_t*)(metadata->entries[i]);
        mcnet_write_int32(out + offset, _entry->data);
        offset += 4;
        break;
      }
      case MCNET_METADATA_TYPE_FLOAT: {
        mcnet_metadata_entry_float_t* _entry = (mcnet_metadata_entry_float_t*)(metadata->entries[i]);
        mcnet_write_float(out + offset, _entry->data);
        offset += 4;
        break;
      }
      case MCNET_METADATA_TYPE_STRING16: {
        mcnet_metadata_entry_string16_t* _entry = (mcnet_metadata_entry_string16_t*)(metadata->entries[i]);
        mcnet_write_uint16(out + offset, _entry->data_length);
        offset += 2;
        memcpy(out + offset, _entry->data, _entry->data_length * 2);
        offset += _entry->data_length * 2;
        break;
      }
      case MCNET_METADATA_TYPE_SLOT: {
        mcnet_metadata_entry_sbs_t* _entry = (mcnet_metadata_entry_sbs_t*)(metadata->entries[i]);
        mcnet_write_uint16(out + offset, _entry->id);
        offset += 2;
        if (_entry->id >= 0) {
          mcnet_write_uint16(out + offset, _entry->count);
          offset += 1;
          mcnet_write_uint16(out + offset, _entry->damage);
          offset += 2;
        }
        break;
      }
      case MCNET_METADATA_TYPE_INTS: {
        mcnet_metadata_entry_iii_t* _entry = (mcnet_metadata_entry_iii_t*)(metadata->entries[i]);
        mcnet_write_uint32(out + offset, _entry->data[0]);
        offset += 4;
        mcnet_write_uint32(out + offset, _entry->data[1]);
        offset += 4;
        mcnet_write_uint32(out + offset, _entry->data[2]);
        offset += 4;
        break;
      }
    }
  }

  out[offset] = 0x7f;

  return offset;
}
