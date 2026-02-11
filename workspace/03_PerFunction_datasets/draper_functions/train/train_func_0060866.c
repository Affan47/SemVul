GetTarget(bool loadIfMissing)
{
	if (target == NULL && loadIfMissing) LoadTarget(NULL);
	return target;
}
