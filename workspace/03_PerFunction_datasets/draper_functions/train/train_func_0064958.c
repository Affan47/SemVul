operator()(change::pointer cp)
{
    if (!cp->is_completed())
        return;

    nstring uuid(cp->uuid_get());
    if (!uuid.empty())
	print_one_line(cp, uuid);

    if (!include_original_uuid)
        return;

    cstate_ty *cstate_data = cp->cstate_get();
    if (cstate_data->attribute)
    {
	for (size_t j = 0; j < cstate_data->attribute->length; ++j)
	{
	    attributes_ty *ap = cstate_data->attribute->list[j];
	    assert(ap);
	    if
    	    (
		ap->name
	    &&
		0 == strcasecmp(ORIGINAL_UUID, ap->name->str_text)
	    &&
		ap->value
	    &&

		universal_unique_identifier_valid(ap->value)
	    )
	    {
		print_one_line(cp, nstring(ap->value));
	    }
	}
    }
}
