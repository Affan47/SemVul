tos_tg_print(const void *ip, const struct xt_entry_target *target,
                         int numeric)
{
	const struct xt_tos_target_info *info = (const void *)target->data;

	if (numeric)
		printf(" TOS set 0x%02x/0x%02x",
		       info->tos_value, info->tos_mask);
	else if (tos_try_print_symbolic(" TOS set",
	    info->tos_value, info->tos_mask))

		return;
	else if (info->tos_value == 0)
		printf(" TOS and 0x%02x",
		       (unsigned int)(uint8_t)~info->tos_mask);
	else if (info->tos_value == info->tos_mask)
		printf(" TOS or 0x%02x", info->tos_value);
	else if (info->tos_mask == 0)
		printf(" TOS xor 0x%02x", info->tos_value);
	else
		printf(" TOS set 0x%02x/0x%02x",
		       info->tos_value, info->tos_mask);
}
