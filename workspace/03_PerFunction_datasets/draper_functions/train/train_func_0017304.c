nvkm_hwsq_wait(struct nvkm_hwsq *hwsq, u8 flag, u8 data)
{
	nvkm_debug(hwsq->subdev, " WAIT[%02x] = %d\n", flag, data);
	hwsq_cmd(hwsq, 3, (u8[]){ 0x5f, flag, data });
}
