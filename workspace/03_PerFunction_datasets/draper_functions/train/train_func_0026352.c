attributes_list_find(attributes_list_ty *alp, const char *name)
{
    if (!alp)
	return 0;
    for (size_t j = 0; j < alp->length; ++j)
    {
	attributes_ty *ap = alp->list[j];
	assert(ap);
	assert(ap->name);
	assert(ap->value);
	if (ap->name && ap->value && 0 == strcasecmp(ap->name->str_text, name))
	    return ap;
    }
    return 0;
}
