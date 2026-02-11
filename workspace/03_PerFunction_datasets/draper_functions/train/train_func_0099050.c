uncore_pmu_to_box(struct intel_uncore_pmu *pmu, int cpu)
{
	struct intel_uncore_box *box;

	box = *per_cpu_ptr(pmu->box, cpu);
	if (box)
		return box;

	raw_spin_lock(&uncore_box_lock);

	if (*per_cpu_ptr(pmu->box, cpu))
		goto out;
	list_for_each_entry(box, &pmu->box_list, list) {
		if (box->phys_id == topology_physical_package_id(cpu)) {
			atomic_inc(&box->refcnt);
			*per_cpu_ptr(pmu->box, cpu) = box;
			break;
		}
	}
out:
	raw_spin_unlock(&uncore_box_lock);

	return *per_cpu_ptr(pmu->box, cpu);
}
