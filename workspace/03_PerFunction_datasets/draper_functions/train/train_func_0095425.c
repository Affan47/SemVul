irmo_object_internal_set(IrmoObject *object,
                              IrmoClassVar *variable,
                              IrmoValue *value,
                              int update_binding)
{
        IrmoValue *obj_value;

	obj_value = &object->variables[variable->index];


	switch (variable->type) {
	case IRMO_TYPE_INT8:
		irmo_return_if_fail(value->i <= 0xff);
		obj_value->i = value->i;
		break;
	case IRMO_TYPE_INT16:
		irmo_return_if_fail(value->i <= 0xffff);
		obj_value->i = value->i;
		break;
	case IRMO_TYPE_INT32:
		obj_value->i = value->i;
		break;
        case IRMO_TYPE_STRING:
                free(obj_value->s);
                obj_value->s = strdup(value->s);
                break;
        default:
                irmo_bug();
        }


        if (update_binding && object->binding != NULL) {
                irmo_object_update_binding(object, variable);
        }


	irmo_object_set_raise(object, variable);
}
