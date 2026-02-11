fixup_static(struct vm_class *vmc)
{
	struct static_fixup_site *this, *next;

	pthread_mutex_lock(&vmc->mutex);

	list_for_each_entry_safe(this, next, &vmc->static_fixup_site_list, vmc_node) {
		struct vm_field *vmf = this->vmf;
		unsigned char *mach_insn;
		int skip_count = 0;
		void *new_target;

		new_target	= vmc->static_values + vmf->offset;
		mach_insn	= buffer_ptr(this->cu->objcode) + this->mach_offset;


		if (is_rex_prefix(*mach_insn))
			skip_count += 1;


		if (is_sse_insn(mach_insn + skip_count))
			skip_count += 4;
		else
			skip_count += 2;

		do_fixup_static(mach_insn, skip_count, new_target);

		list_del(&this->vmc_node);

		pthread_mutex_lock(&this->cu->mutex);
		list_del(&this->cu_node);
		pthread_mutex_unlock(&this->cu->mutex);

		free(this);
	}

	pthread_mutex_unlock(&vmc->mutex);
}
