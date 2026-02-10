nvkm_memx_nsec(struct nvkm_memx *memx, u32 nsec)
{
	nvkm_debug(&memx->pmu->subdev, "    DELAY = %d ns\n", nsec);
	memx_cmd(memx, MEMX_DELAY, 1, (u32[]){ nsec });
	memx_out(memx);
}
