popConditional (void)
{
	if (Cpp.directive.nestLevel > 0)
		--Cpp.directive.nestLevel;

	return isIgnore ();
}
