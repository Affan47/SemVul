kvm_hv_msr_get_crash_data(struct kvm_vcpu *vcpu,
				     u32 index, u64 *pdata)
{
	struct kvm_hv *hv = &vcpu->kvm->arch.hyperv;

	if (WARN_ON_ONCE(index >= ARRAY_SIZE(hv->hv_crash_param)))
		return -EINVAL;

	*pdata = hv->hv_crash_param[index];
	return 0;
}
