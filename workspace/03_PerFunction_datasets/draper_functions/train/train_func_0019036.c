videocodec_unregister (const struct videocodec *codec)
{
	struct codec_list *prev = NULL, *h = codeclist_top;

	if (!codec) {
		dprintk(1, KERN_ERR "videocodec_unregister: no data!\n");
		return -EINVAL;
	}

	dprintk(2,
		"videocodec: unregister '%s', type: %x, flags %lx, magic %lx\n",
		codec->name, codec->type, codec->flags, codec->magic);

	if (!h) {
		dprintk(1,
			KERN_ERR
			"videocodec_unregister: no device left...\n");
		return -ENXIO;
	}

	while (h) {
		if (codec == h->codec) {
			if (h->attached) {
				dprintk(1,
					KERN_ERR
					"videocodec: '%s' is used\n",
					h->codec->name);
				return -EBUSY;
			}
			dprintk(3, "videocodec: unregister '%s' is ok.\n",
				h->codec->name);
			if (prev == NULL) {
				codeclist_top = h->next;
				dprintk(4,
					"videocodec: delete first element\n");
			} else {
				prev->next = h->next;
				dprintk(4,
					"videocodec: delete middle element\n");
			}
			kfree(h);
			return 0;
		}
		prev = h;
		h = h->next;
	}

	dprintk(1,
		KERN_ERR
		"videocodec_unregister: given codec not found!\n");
	return -EINVAL;
}
