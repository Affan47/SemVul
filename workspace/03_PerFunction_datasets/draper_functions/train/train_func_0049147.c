nvkm_disp_vblank_ctor(struct nvkm_object *object, void *data, u32 size,
		      struct nvkm_notify *notify)
{
	struct nvkm_disp *disp =
		container_of(notify->event, typeof(*disp), vblank);
	union {
		struct nvif_notify_head_req_v0 v0;
	} *req = data;
	int ret;

	if (nvif_unpack(req->v0, 0, 0, false)) {
		notify->size = sizeof(struct nvif_notify_head_rep_v0);
		if (ret = -ENXIO, req->v0.head <= disp->vblank.index_nr) {
			notify->types = 1;
			notify->index = req->v0.head;
			return 0;
		}
	}

	return ret;
}
