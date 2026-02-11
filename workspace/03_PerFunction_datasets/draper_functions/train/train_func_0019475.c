record_sample(bool prolog_p)
{
	profiling_sample_count counts = safepoint.sample_counts.record_counts();
	if (!counts.empty())
		samples.push_back(profiling_sample(this, prolog_p,
			counts, special_objects[OBJ_CURRENT_THREAD]));
}
