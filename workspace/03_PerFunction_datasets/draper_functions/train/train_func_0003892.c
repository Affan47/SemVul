class_method_pair_equal (gconstpointer ka, gconstpointer kb)
{
	const MonoClassMethodPair *apair = (const MonoClassMethodPair *)ka;
	const MonoClassMethodPair *bpair = (const MonoClassMethodPair *)kb;

	return apair->klass == bpair->klass && apair->method == bpair->method ? 1 : 0;
}
