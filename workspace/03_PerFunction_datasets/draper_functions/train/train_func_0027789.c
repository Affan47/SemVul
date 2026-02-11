emitmodrm_mod(int mod)
{
	if (modrmv == -1) modrmv = 0;
	modrmv = (modrmv & ~(3<<6)) | ((mod & 3)<<6);
}
