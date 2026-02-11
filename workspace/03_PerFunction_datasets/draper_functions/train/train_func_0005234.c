test_injective(isl_ctx *ctx)
{
	const char *str;

	if (test_plain_injective(ctx, "{S[i,j] -> A[0]; T[i,j] -> B[1]}", 0))
		return -1;
	if (test_plain_injective(ctx, "{S[] -> A[0]; T[] -> B[0]}", 1))
		return -1;
	if (test_plain_injective(ctx, "{S[] -> A[0]; T[] -> A[1]}", 1))
		return -1;
	if (test_plain_injective(ctx, "{S[] -> A[0]; T[] -> A[0]}", 0))
		return -1;
	if (test_plain_injective(ctx, "{S[i] -> A[i,0]; T[i] -> A[i,1]}", 1))
		return -1;
	if (test_plain_injective(ctx, "{S[i] -> A[i]; T[i] -> A[i]}", 0))
		return -1;
	if (test_plain_injective(ctx, "{S[] -> A[0,0]; T[] -> A[0,1]}", 1))
		return -1;
	if (test_plain_injective(ctx, "{S[] -> A[0,0]; T[] -> A[1,0]}", 1))
		return -1;

	str = "{S[] -> A[0,0]; T[] -> A[0,1]; U[] -> A[1,0]}";
	if (test_plain_injective(ctx, str, 1))
		return -1;
	str = "{S[] -> A[0,0]; T[] -> A[0,1]; U[] -> A[0,0]}";
	if (test_plain_injective(ctx, str, 0))
		return -1;

	return 0;
}
