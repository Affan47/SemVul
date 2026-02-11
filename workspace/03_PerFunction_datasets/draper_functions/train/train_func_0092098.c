ktime_add_safe(const ktime_t lhs, const ktime_t rhs)
{
	ktime_t res = ktime_add_unsafe(lhs, rhs);


	if (res.tv64 < 0 || res.tv64 < lhs.tv64 || res.tv64 < rhs.tv64)
		res = ktime_set(KTIME_SEC_MAX, 0);

	return res;
}
