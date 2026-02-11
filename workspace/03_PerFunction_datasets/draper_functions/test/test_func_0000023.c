vmlfb_disable_pipe(struct vml_info *vinfo)
{
	struct vml_par *par = vinfo->par;


	VML_WRITE32(par, VML_RCOMPSTAT, 0);
	while (!(VML_READ32(par, VML_RCOMPSTAT) & VML_MDVO_VDC_I_RCOMP)) ;


	VML_WRITE32(par, VML_DSPCCNTR,
		    VML_READ32(par, VML_DSPCCNTR) & ~VML_GFX_ENABLE);
	(void)VML_READ32(par, VML_DSPCCNTR);

	vml_wait_vblank(vinfo);


	VML_WRITE32(par, VML_PIPEACONF, 0);
	(void)VML_READ32(par, VML_PIPEACONF);

	vinfo->pipe_disabled = 1;
}
