solve(SharedContext& ctx, const SolveParams& p, const LitVec& assume) {
	assumptions_ = assume;
	if (!isSentinel(ctx.tagLiteral())) { assumptions_.push_back(ctx.tagLiteral()); }
	bool more = limits_.conflicts == 0 || doSolve(*ctx.master(), p);
	ctx.enumerator()->reportResult(!more);
	if (!isSentinel(ctx.tagLiteral())) { assumptions_.pop_back(); }
	ctx.detach(*ctx.master());
	return more;
}
