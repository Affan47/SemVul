cik_sdma_resume(struct radeon_device *rdev)
{
	int r;

	r = cik_sdma_load_microcode(rdev);
	if (r)
		return r;


	cik_sdma_enable(rdev, true);


	r = cik_sdma_gfx_resume(rdev);
	if (r)
		return r;
	r = cik_sdma_rlc_resume(rdev);
	if (r)
		return r;

	return 0;
}
