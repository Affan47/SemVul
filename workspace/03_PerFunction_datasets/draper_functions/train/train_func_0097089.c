nvkm_memx_fini(struct nvkm_memx **pmemx, bool exec)
{
	struct nvkm_memx *memx = *pmemx;
	struct nvkm_pmu *pmu = memx->pmu;
	struct nvkm_subdev *subdev = &pmu->subdev;
	struct nvkm_device *device = subdev->device;
	u32 finish, reply[2];


	memx_out(memx);


	finish = nvkm_rd32(device, 0x10a1c0) & 0x00ffffff;
	nvkm_wr32(device, 0x10a580, 0x00000000);


	if (exec) {
		nvkm_pmu_send(pmu, reply, PROC_MEMX, MEMX_MSG_EXEC,
			      memx->base, finish);
	}

	nvkm_debug(subdev, "Exec took %uns, PMU_IN %08x\n",
		   reply[0], reply[1]);
	kfree(memx);
	return 0;
}
