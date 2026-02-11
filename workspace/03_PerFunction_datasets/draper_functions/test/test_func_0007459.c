resourcecmp (const void *first, const void *second)
{
	if (((resource_t *)first)->type ==
	    ((resource_t *)second)->type)
		return (((resource_t *)first)->number <
			((resource_t *)second)->number)? -1 :
		!(((resource_t *)first)->number ==
		  ((resource_t *)second)->number);
	else
		return (((resource_t *)first)->type <
			((resource_t *)second)->type)? -1 : 1;
}
