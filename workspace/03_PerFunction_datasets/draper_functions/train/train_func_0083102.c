bios_15_87xx(struct regs *regs)
{
	unsigned char prev_a20_enable;
	unsigned long base;
	uint16_t cx;
	uint16_t di;
	uint16_t si;
	unsigned long tmp;


	disable_ints();


	prev_a20_enable = set_enable_a20(1);


	base = ((unsigned long) ES << 4) + (unsigned long) SI;
	put_word(ES, SI + 0x08 + 0, 47);
	put_word(ES, SI + 0x08 + 2, base & 0xffff);
	put_byte(ES, SI + 0x08 + 4, base >> 16);
	put_byte(ES, SI + 0x08 + 5, 0x93);
	put_word(ES, SI + 0x08 + 6, 0x0000);


	base = (unsigned long) bios_15_87xx;
	put_word(ES, SI + 0x20 + 0, 0xffff);
	put_word(ES, SI + 0x20 + 2, base & 0xffff);
	put_byte(ES, SI + 0x20 + 4, base >> 16);
	put_byte(ES, SI + 0x20 + 5, 0x9b);
	put_word(ES, SI + 0x20 + 6, 0x0000);


	base = (unsigned long) get_ss() << 4;
	put_word(ES, SI + 0x28 + 0, 0xffff);
	put_word(ES, SI + 0x28 + 2, base & 0xffff);
	put_byte(ES, SI + 0x28 + 4, base >> 16);
	put_byte(ES, SI + 0x28 + 5, 0x93);
	put_word(ES, SI + 0x28 + 6, 0x0000);


	asm volatile (
		"movw %0, %%es\n"
		"lgdt %%es:(%1)\n"
		:
		: "r" ((uint16_t)ES), "S" ((uint16_t)(SI + 8))
	);


	asm volatile (
		"pushaw\n"
		"pushfw\n"
#ifdef CONFIG_80286_SUPPORT

		"movb $0x0f, %%al\n"
		"outb %%al, $0x70\n"
		"movb $0x05, %%al\n"
		"outb %%al, $0x71\n"
#endif

		"movw $0x0040, %%bx\n"
		"movw %%ds, %%ax\n"
		"movw %%bx, %%ds\n"

		"movw $0x0072, %%bx\n"
		"movw $0x1234, (%%bx)\n"

		"movw $0x00f0, %%bx\n"
		"movw %%sp, (%%bx)\n"
		"movw $0x00f2, %%bx\n"
		"movw %%ss, (%%bx)\n"
		"movw $0x00f4, %%bx\n"
		"movw %%ax, (%%bx)\n"
		"movw $0x00f6, %%bx\n"
		"movw %%es, (%%bx)\n"

		"movw $0x0067, %%bx\n"
		"movw $(leave_pmode - bios_15_87xx), %%ax\n"
		"addw $OFF_bios_15_87xx, %%ax\n"
		"movw %%ax, (%%bx)\n"
		"movw $0x0069, %%bx\n"
		"movw %%cs, (%%bx)\n"


		"smsww %w0\n"
		"orw $0x0001, %w0\n"
		"lmsww %w0\n"

		"ljmp $0x0020, $(enter_pmode - bios_15_87xx)\n"
	"enter_pmode:\n"


		"mov $0x0010, %0\n"
		"mov %0, %%ds\n"
		"mov $0x0018, %0\n"
		"mov %0, %%es\n"
		"movw $0x0000, %%si\n"
		"movw $0x0000, %%di\n"
		"cld\n"
		"rep movsw\n"

#ifdef CONFIG_80286_SUPPORT

		"movb $0x4, %%al\n"
		"movw $0xcf9, %%dx\n"
		"out  %%al, (%%dx)\n"

	"1:\n"
		"jmp 1b\n"
#else

		"movl %%cr0, %0\n"
		"andl $~(1 << 0), %0\n"
		"movl %0, %%cr0\n"
		"ex_ljmp leave_pmode\n"
#endif
	"leave_pmode:\n"


		"movw $0x0040, %%bx\n"
		"movw %%bx, %%ds\n"
		"movw $0x00f0, %%bx\n"
		"movw (%%bx), %%sp\n"
		"movw $0x00f2, %%bx\n"
		"movw (%%bx), %%ss\n"
		"movw $0x00f4, %%bx\n"
		"movw (%%bx), %%ds\n"
		"movw $0x00f6, %%bx\n"
		"movw (%%bx), %%es\n"
		"popfw\n"
		"popaw\n"

		: "=r" (tmp), "=D" (di), "=S" (si), "=c" (cx)
		: "3" (CX)
	);


	set_enable_a20(prev_a20_enable);


	enable_ints();

	AH = 0x00;
	F &= ~(1 << 0);
}
