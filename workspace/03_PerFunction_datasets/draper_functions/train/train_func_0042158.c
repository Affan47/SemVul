parser_init_byte_stream(u64 addr, u32 bytes, bool local, bool *retry)
{
	int allocbytes = sizeof(struct parser_context) + bytes;
	struct parser_context *rc = NULL;
	struct parser_context *ctx = NULL;

	if (retry)
		*retry = false;


	allocbytes++;
	if ((controlvm_payload_bytes_buffered + bytes)
	    > MAX_CONTROLVM_PAYLOAD_BYTES) {
		if (retry)
			*retry = true;
		rc = NULL;
		goto cleanup;
	}
	ctx = kzalloc(allocbytes, GFP_KERNEL|__GFP_NORETRY);
	if (!ctx) {
		if (retry)
			*retry = true;
		rc = NULL;
		goto cleanup;
	}

	ctx->allocbytes = allocbytes;
	ctx->param_bytes = bytes;
	ctx->curr = NULL;
	ctx->bytes_remaining = 0;
	ctx->byte_stream = false;
	if (local) {
		void *p;

		if (addr > virt_to_phys(high_memory - 1)) {
			rc = NULL;
			goto cleanup;
		}
		p = __va((unsigned long) (addr));
		memcpy(ctx->data, p, bytes);
	} else {
		void *mapping;

		if (!request_mem_region(addr, bytes, "visorchipset")) {
			rc = NULL;
			goto cleanup;
		}

		mapping = memremap(addr, bytes, MEMREMAP_WB);
		if (!mapping) {
			release_mem_region(addr, bytes);
			rc = NULL;
			goto cleanup;
		}
		memcpy(ctx->data, mapping, bytes);
		release_mem_region(addr, bytes);
		memunmap(mapping);
	}

	ctx->byte_stream = true;
	rc = ctx;
cleanup:
	if (rc) {
		controlvm_payload_bytes_buffered += ctx->param_bytes;
	} else {
		if (ctx) {
			parser_done(ctx);
			ctx = NULL;
		}
	}
	return rc;
}
