safe_getenv(const struct tls_info *info, const char *n)
{
	const char *v=(*info->getconfigvar)(n, info->app_data);

	if (!v)	v="";
	return (v);
}
