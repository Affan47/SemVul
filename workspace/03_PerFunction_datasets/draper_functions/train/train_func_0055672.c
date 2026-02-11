_comedi_arm(comedi_t *device, unsigned subdevice, unsigned target)
{
	comedi_insn insn;
	lsampl_t data[2];

	memset(&insn, 0, sizeof(comedi_insn));
	insn.insn = INSN_CONFIG;
	insn.subdev = subdevice;
	insn.chanspec = 0;
	insn.data = data;
	insn.n = sizeof(data) / sizeof(data[0]);
	data[0] = INSN_CONFIG_ARM;
	data[1] = target;

	if(comedi_do_insn(device, &insn) >= 0) return 0;
	else return -1;
}
