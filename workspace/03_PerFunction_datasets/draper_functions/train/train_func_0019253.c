kernfs_vma_set_policy(struct vm_area_struct *vma,
				 struct mempolicy *new)
{
	struct file *file = vma->vm_file;
	struct kernfs_open_file *of = kernfs_of(file);
	int ret;

	if (!of->vm_ops)
		return 0;

	if (!kernfs_get_active(of->kn))
		return -EINVAL;

	ret = 0;
	if (of->vm_ops->set_policy)
		ret = of->vm_ops->set_policy(vma, new);

	kernfs_put_active(of->kn);
	return ret;
}
