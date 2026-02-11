gmc_v8_0_mc_init(struct amdgpu_device *adev)
{
	u32 tmp;
	int chansize, numchan;


	tmp = RREG32(mmMC_ARB_RAMCFG);
	if (REG_GET_FIELD(tmp, MC_ARB_RAMCFG, CHANSIZE)) {
		chansize = 64;
	} else {
		chansize = 32;
	}
	tmp = RREG32(mmMC_SHARED_CHMAP);
	switch (REG_GET_FIELD(tmp, MC_SHARED_CHMAP, NOOFCHAN)) {
	case 0:
	default:
		numchan = 1;
		break;
	case 1:
		numchan = 2;
		break;
	case 2:
		numchan = 4;
		break;
	case 3:
		numchan = 8;
		break;
	case 4:
		numchan = 3;
		break;
	case 5:
		numchan = 6;
		break;
	case 6:
		numchan = 10;
		break;
	case 7:
		numchan = 12;
		break;
	case 8:
		numchan = 16;
		break;
	}
	adev->mc.vram_width = numchan * chansize;

	adev->mc.aper_base = pci_resource_start(adev->pdev, 0);
	adev->mc.aper_size = pci_resource_len(adev->pdev, 0);

	adev->mc.mc_vram_size = RREG32(mmCONFIG_MEMSIZE) * 1024ULL * 1024ULL;
	adev->mc.real_vram_size = RREG32(mmCONFIG_MEMSIZE) * 1024ULL * 1024ULL;
	adev->mc.visible_vram_size = adev->mc.aper_size;


	if (adev->mc.visible_vram_size > adev->mc.real_vram_size)
		adev->mc.visible_vram_size = adev->mc.real_vram_size;


	if (amdgpu_gart_size == -1)
		adev->mc.gtt_size = max((1024ULL << 20), adev->mc.mc_vram_size);
	else
		adev->mc.gtt_size = (uint64_t)amdgpu_gart_size << 20;

	gmc_v8_0_vram_gtt_location(adev, &adev->mc);

	return 0;
}
