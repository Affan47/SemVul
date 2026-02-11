PM3_WAIT(struct pm3_par *par, u32 n)
{
	while (PM3_READ_REG(par, PM3InFIFOSpace) < n)
		cpu_relax();
}
