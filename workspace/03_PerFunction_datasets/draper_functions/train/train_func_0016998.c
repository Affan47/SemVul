sst_platform_compr_open(struct snd_compr_stream *cstream)
{

	int ret_val = 0;
	struct snd_compr_runtime *runtime = cstream->runtime;
	struct sst_runtime_stream *stream;

	stream = kzalloc(sizeof(*stream), GFP_KERNEL);
	if (!stream)
		return -ENOMEM;

	spin_lock_init(&stream->status_lock);


	if (!sst || !try_module_get(sst->dev->driver->owner)) {
		pr_err("no device available to run\n");
		ret_val = -ENODEV;
		goto out_ops;
	}
	stream->compr_ops = sst->compr_ops;
	stream->id = 0;


	sst->compr_ops->power(sst->dev, true);

	sst_set_stream_status(stream, SST_PLATFORM_INIT);
	runtime->private_data = stream;
	return 0;
out_ops:
	kfree(stream);
	return ret_val;
}
