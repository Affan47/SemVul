execute_flush_op(H5F_t * file_ptr,
		 struct test_entry_t * entry_ptr,
		 struct flush_op * op_ptr,
		 unsigned * flags_ptr)
{
    H5C_t * cache_ptr;

    HDassert( file_ptr );
    cache_ptr = file_ptr->shared->cache;
    HDassert( cache_ptr != NULL );
    HDassert( cache_ptr->magic == H5C__H5C_T_MAGIC );
    HDassert( entry_ptr != NULL );
    HDassert( entry_ptr = entry_ptr->self );
    HDassert( entry_ptr->header.addr == entry_ptr->addr );
    HDassert( ( entry_ptr->flush_op_self_resize_in_progress ) ||
              ( entry_ptr->header.size == entry_ptr->size ) );
    HDassert( op_ptr != NULL );
    HDassert( ( 0 <= entry_ptr->type ) &&
              ( entry_ptr->type < NUMBER_OF_ENTRY_TYPES ) );
    HDassert( ( 0 <= entry_ptr->index ) &&
              ( entry_ptr->index <= max_indices[entry_ptr->type] ) );
    HDassert( ( 0 <= op_ptr->type ) &&
              ( op_ptr->type < NUMBER_OF_ENTRY_TYPES ) );
    HDassert( ( 0 <= op_ptr->idx ) &&
              ( op_ptr->idx <= max_indices[op_ptr->type] ) );
    HDassert( ( op_ptr->flag == FALSE ) || ( op_ptr->flag == TRUE ) );
    HDassert( flags_ptr != NULL );

    if ( pass ) {

	switch ( op_ptr->op_code )
	{
	    case FLUSH_OP__NO_OP:
		break;

	    case FLUSH_OP__DIRTY:
		HDassert( ( entry_ptr->type != op_ptr->type ) ||
			  ( entry_ptr->index != op_ptr->idx ) );

		dirty_entry(file_ptr, op_ptr->type, op_ptr->idx, op_ptr->flag);
		break;

            case FLUSH_OP__RESIZE:
		if ( ( entry_ptr->type == op_ptr->type ) &&
                     ( entry_ptr->index == op_ptr->idx ) ) {


                    HDassert( entry_ptr->type == VARIABLE_ENTRY_TYPE );
		    HDassert( op_ptr->size > 0 );
		    HDassert( op_ptr->size <= VARIABLE_ENTRY_SIZE );

                    entry_ptr->size = op_ptr->size;
		    (*flags_ptr) |= H5C_CALLBACK__SIZE_CHANGED_FLAG;
		    entry_ptr->flush_op_self_resize_in_progress = TRUE;


		    if ( entry_ptr->header.destroy_in_progress ) {

			entry_ptr->header.size = entry_ptr->size;
		    }

		} else {


		    resize_entry(file_ptr, op_ptr->type, op_ptr->idx,
                                 op_ptr->size, op_ptr->flag);
		}
		break;

	    case FLUSH_OP__MOVE:
		move_entry(cache_ptr, op_ptr->type, op_ptr->idx,
			     op_ptr->flag);
		break;

	    default:
                pass = FALSE;
                failure_mssg = "Undefined flush op code.";
		break;
	}
    }

    return;

}
