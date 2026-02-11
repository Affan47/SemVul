object_sense_artifact(object_type *o_ptr)
{
	if (artifact_p(o_ptr))
		object_notice_sensing(o_ptr);
	else
		o_ptr->ident |= IDENT_NOTART;
}
