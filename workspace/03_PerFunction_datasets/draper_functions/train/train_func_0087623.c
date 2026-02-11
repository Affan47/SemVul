DecreaseEmulationSpeed(void)
{
	g_fpsScale /= LOGMUL;
	if(g_fpsScale < Slowest)
		g_fpsScale = Slowest;

	RefreshThrottleFPS();

	FCEU_DispMessage("Emulation speed %.1f%%",0, g_fpsScale*100.0);
}
