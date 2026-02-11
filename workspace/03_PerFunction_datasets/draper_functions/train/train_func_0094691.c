AnimationStacks() const
{
	if (!animationStacksResolved.empty() || animationStacks.empty()) {
		return animationStacksResolved;
	}

	animationStacksResolved.reserve(animationStacks.size());
	BOOST_FOREACH(uint64_t id, animationStacks) {
		LazyObject* const lazy = GetObject(id);
		const AnimationStack* stack;
		if(!lazy || !(stack = lazy->Get<AnimationStack>())) {
			DOMWarning("failed to read AnimationStack object");
			continue;
		}
		animationStacksResolved.push_back(stack);
	}

	return animationStacksResolved;
}
