esas2r_read_flash_rev(struct esas2r_adapter *a)
{
	u8 bytes[256];
	u16 *pw;
	u16 *pwstart;
	u16 type;
	u16 size;
	u32 sz;

	sz = sizeof(bytes);
	pw = (u16 *)(bytes + sz);
	pwstart = (u16 *)bytes + 2;

	if (!esas2r_read_flash_block(a, bytes, FLS_OFFSET_CPYR - sz, sz))
		goto invalid_rev;

	while (pw >= pwstart) {
		pw--;
		type = le16_to_cpu(*pw);
		pw--;
		size = le16_to_cpu(*pw);
		pw -= size / 2;

		if (type == FBT_CPYR
		    || type == FBT_SETUP
		    || pw < pwstart)
			continue;

		if (type == FBT_FLASH_VER)
			a->flash_ver = le32_to_cpu(*(u32 *)pw);

		break;
	}

invalid_rev:
	return esas2r_print_flash_rev(a);
}
