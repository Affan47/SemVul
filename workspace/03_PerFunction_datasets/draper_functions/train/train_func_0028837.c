read_pointer(const u8 **pLoc,
                                  const void *end,
                                  signed ptrType)
{
	unsigned long value = 0;
	union {
		const u8 *p8;
		const u16 *p16u;
		const s16 *p16s;
		const u32 *p32u;
		const s32 *p32s;
		const unsigned long *pul;
	} ptr;

	if (ptrType < 0 || ptrType == DW_EH_PE_omit)
		return 0;
	ptr.p8 = *pLoc;
	switch(ptrType & DW_EH_PE_FORM) {
	case DW_EH_PE_data2:
		if (end < (const void *)(ptr.p16u + 1))
			return 0;
		if(ptrType & DW_EH_PE_signed)
			value = get_unaligned(ptr.p16s++);
		else
			value = get_unaligned(ptr.p16u++);
		break;
	case DW_EH_PE_data4:
#ifdef CONFIG_64BIT
		if (end < (const void *)(ptr.p32u + 1))
			return 0;
		if(ptrType & DW_EH_PE_signed)
			value = get_unaligned(ptr.p32s++);
		else
			value = get_unaligned(ptr.p32u++);
		break;
	case DW_EH_PE_data8:
		BUILD_BUG_ON(sizeof(u64) != sizeof(value));
#else
		BUILD_BUG_ON(sizeof(u32) != sizeof(value));
#endif
	case DW_EH_PE_native:
		if (end < (const void *)(ptr.pul + 1))
			return 0;
		value = get_unaligned(ptr.pul++);
		break;
	case DW_EH_PE_leb128:
		BUILD_BUG_ON(sizeof(uleb128_t) > sizeof(value));
		value = ptrType & DW_EH_PE_signed
		        ? get_sleb128(&ptr.p8, end)
		        : get_uleb128(&ptr.p8, end);
		if ((const void *)ptr.p8 > end)
			return 0;
		break;
	default:
		return 0;
	}
	switch(ptrType & DW_EH_PE_ADJUST) {
	case DW_EH_PE_abs:
		break;
	case DW_EH_PE_pcrel:
		value += (unsigned long)*pLoc;
		break;
	default:
		return 0;
	}


	*pLoc = ptr.p8;

	return value;
}
