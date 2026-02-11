set_audio_standard_EIAJ(struct cx88_core *core)
{
	static const struct rlist eiaj[] = {


		{  },
	};
	dprintk("%s (status: unknown)\n", __func__);

	set_audio_start(core, SEL_EIAJ);
	set_audio_registers(core, eiaj);
	set_audio_finish(core, EN_EIAJ_AUTO_STEREO);
}
