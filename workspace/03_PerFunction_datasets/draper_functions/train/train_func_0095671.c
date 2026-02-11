nvkm_perfsrc_new(struct nvkm_pm *pm, struct nvkm_perfsig *sig,
		 const struct nvkm_specsrc *spec)
{
	const struct nvkm_specsrc *ssrc;
	const struct nvkm_specmux *smux;
	struct nvkm_perfsrc *src;
	u8 source_nr = 0;

	if (!spec) {

		return 0;
	}

	ssrc = spec;
	while (ssrc->name) {
		smux = ssrc->mux;
		while (smux->name) {
			bool found = false;
			u8 source_id = 0;
			u32 len;

			list_for_each_entry(src, &pm->sources, head) {
				if (src->addr == ssrc->addr &&
				    src->shift == smux->shift) {
					found = true;
					break;
				}
				source_id++;
			}

			if (!found) {
				src = kzalloc(sizeof(*src), GFP_KERNEL);
				if (!src)
					return -ENOMEM;

				src->addr   = ssrc->addr;
				src->mask   = smux->mask;
				src->shift  = smux->shift;
				src->enable = smux->enable;

				len = strlen(ssrc->name) +
				      strlen(smux->name) + 2;
				src->name = kzalloc(len, GFP_KERNEL);
				if (!src->name) {
					kfree(src);
					return -ENOMEM;
				}
				snprintf(src->name, len, "%s_%s", ssrc->name,
					 smux->name);

				list_add_tail(&src->head, &pm->sources);
			}

			sig->source[source_nr++] = source_id + 1;
			smux++;
		}
		ssrc++;
	}

	return 0;
}
