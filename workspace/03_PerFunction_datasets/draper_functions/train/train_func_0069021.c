i915_gem_dmabuf_mmap(struct dma_buf *dma_buf, struct vm_area_struct *vma)
{
	struct drm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	int ret;

	if (obj->base.size < vma->vm_end - vma->vm_start)
		return -EINVAL;

	if (!obj->base.filp)
		return -ENODEV;

	ret = obj->base.filp->f_op->mmap(obj->base.filp, vma);
	if (ret)
		return ret;

	fput(vma->vm_file);
	vma->vm_file = get_file(obj->base.filp);

	return 0;
}
