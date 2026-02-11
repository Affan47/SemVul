mod_src_encode(uint64_t flags)
{
	switch (flags & SRC_MASK) {
	case SRC_MEMDISP:
	case SRC_MEM:
		return 0x00;
	case SRC_MEM_DISP_BYTE:
		return 0x01;
	case SRC_MEM_DISP_FULL:
	case SRC_MEMLOCAL:
		return 0x02;
	case SRC_REG:
		return 0x03;
	default:
		break;
	}

	die("unrecognized flags %" PRIx64, flags & SRC_MASK);
}
