native_io_delay(void)
{
	switch (io_delay_type) {
	default:
	case CONFIG_IO_DELAY_TYPE_0X80:
		asm volatile ("outb %al, $0x80");
		break;
	case CONFIG_IO_DELAY_TYPE_0XED:
		asm volatile ("outb %al, $0xed");
		break;
	case CONFIG_IO_DELAY_TYPE_UDELAY:


		udelay(2);
	case CONFIG_IO_DELAY_TYPE_NONE:
		break;
	}
}
