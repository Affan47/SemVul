il4965_load_firmware(struct il_priv *il, const struct firmware *ucode_raw,
		     struct il4965_firmware_pieces *pieces)
{
	struct il_ucode_header *ucode = (void *)ucode_raw->data;
	u32 api_ver, hdr_size;
	const u8 *src;

	il->ucode_ver = le32_to_cpu(ucode->ver);
	api_ver = IL_UCODE_API(il->ucode_ver);

	switch (api_ver) {
	default:
	case 0:
	case 1:
	case 2:
		hdr_size = 24;
		if (ucode_raw->size < hdr_size) {
			IL_ERR("File size too small!\n");
			return -EINVAL;
		}
		pieces->inst_size = le32_to_cpu(ucode->v1.inst_size);
		pieces->data_size = le32_to_cpu(ucode->v1.data_size);
		pieces->init_size = le32_to_cpu(ucode->v1.init_size);
		pieces->init_data_size = le32_to_cpu(ucode->v1.init_data_size);
		pieces->boot_size = le32_to_cpu(ucode->v1.boot_size);
		src = ucode->v1.data;
		break;
	}


	if (ucode_raw->size !=
	    hdr_size + pieces->inst_size + pieces->data_size +
	    pieces->init_size + pieces->init_data_size + pieces->boot_size) {

		IL_ERR("uCode file size %d does not match expected size\n",
		       (int)ucode_raw->size);
		return -EINVAL;
	}

	pieces->inst = src;
	src += pieces->inst_size;
	pieces->data = src;
	src += pieces->data_size;
	pieces->init = src;
	src += pieces->init_size;
	pieces->init_data = src;
	src += pieces->init_data_size;
	pieces->boot = src;
	src += pieces->boot_size;

	return 0;
}
