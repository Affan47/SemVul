operator()(object *obj, cell size)
	{
		parent->data->tenured->starts.record_object_start_offset(obj);

		data_visitor.visit_slots(obj);

		switch(obj->type())
		{
		case ALIEN_TYPE:
			{

				alien *ptr = (alien *)obj;

				if(to_boolean(ptr->base))
					ptr->update_address();
				else
					ptr->expired = parent->true_object;
				break;
			}
		case DLL_TYPE:
			{
				parent->ffi_dlopen((dll *)obj);
				break;
			}
		default:
			{
				code_visitor.visit_object_code_block(obj);
				break;
			}
		}
	}
