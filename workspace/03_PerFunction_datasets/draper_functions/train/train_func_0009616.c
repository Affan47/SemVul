jmlist_replace_by_index(jmlist jml,jmlist_index index,void *new_ptr)
{
	jmlist_debug(__func__,"called with jml=%p, index=%u, new_ptr=%p",jml,index,new_ptr);

	if( jml->flags & JMLIST_INDEXED )
	{
		jmlist_debug(__func__,"passing control to indexed list replace_by_index routine.");
		return ijmlist_idx_replace_by_index(jml,index,new_ptr);
	} else if( jml->flags & JMLIST_LINKED )
	{
		jmlist_debug(__func__,"passing control to linked list replace_by_index routine.");
		return ijmlist_lnk_replace_by_index(jml,index,new_ptr);
	} else if( jml->flags & JMLIST_ASSOCIATIVE )
	{
		jmlist_debug(__func__,"passing control to the associative list replace_by_index routine.");
		return ijmlist_ass_replace_by_index(jml,index,new_ptr);
	}

	jmlist_debug(__func__,"invalid or unsupported list type (jml=%p, flags=%u)",jml,jml->flags);
	jmlist_debug(__func__,"returning with failure.");
	jmlist_errno = JMLIST_ERROR_INVALID_ARGUMENT;
	return JMLIST_ERROR_FAILURE;
}
