nv40_gr_intr(struct nvkm_gr *base)
{
	struct nv40_gr *gr = nv40_gr(base);
	struct nv40_gr_chan *temp, *chan = NULL;
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, NV03_PGRAPH_INTR);
	u32 nsource = nvkm_rd32(device, NV03_PGRAPH_NSOURCE);
	u32 nstatus = nvkm_rd32(device, NV03_PGRAPH_NSTATUS);
	u32 inst = nvkm_rd32(device, 0x40032c) & 0x000fffff;
	u32 addr = nvkm_rd32(device, NV04_PGRAPH_TRAPPED_ADDR);
	u32 subc = (addr & 0x00070000) >> 16;
	u32 mthd = (addr & 0x00001ffc);
	u32 data = nvkm_rd32(device, NV04_PGRAPH_TRAPPED_DATA);
	u32 class = nvkm_rd32(device, 0x400160 + subc * 4) & 0xffff;
	u32 show = stat;
	char msg[128], src[128], sta[128];
	unsigned long flags;

	spin_lock_irqsave(&gr->base.engine.lock, flags);
	list_for_each_entry(temp, &gr->chan, head) {
		if (temp->inst >> 4 == inst) {
			chan = temp;
			list_del(&chan->head);
			list_add(&chan->head, &gr->chan);
			break;
		}
	}

	if (stat & NV_PGRAPH_INTR_ERROR) {
		if (nsource & NV03_PGRAPH_NSOURCE_DMA_VTX_PROTECTION) {
			nvkm_mask(device, 0x402000, 0, 0);
		}
	}

	nvkm_wr32(device, NV03_PGRAPH_INTR, stat);
	nvkm_wr32(device, NV04_PGRAPH_FIFO, 0x00000001);

	if (show) {
		nvkm_snprintbf(msg, sizeof(msg), nv10_gr_intr_name, show);
		nvkm_snprintbf(src, sizeof(src), nv04_gr_nsource, nsource);
		nvkm_snprintbf(sta, sizeof(sta), nv10_gr_nstatus, nstatus);
		nvkm_error(subdev, "intr %08x [%s] nsource %08x [%s] "
				   "nstatus %08x [%s] ch %d [%08x %s] subc %d "
				   "class %04x mthd %04x data %08x\n",
			   show, msg, nsource, src, nstatus, sta,
			   chan ? chan->fifo->chid : -1, inst << 4,
			   chan ? chan->fifo->object.client->name : "unknown",
			   subc, class, mthd, data);
	}

	spin_unlock_irqrestore(&gr->base.engine.lock, flags);
}
