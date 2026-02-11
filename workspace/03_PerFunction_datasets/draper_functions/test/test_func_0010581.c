irmo_object_get(IrmoObject *object, IrmoClassVar *variable,
                     IrmoValue *value)
{
	irmo_return_if_fail(object != NULL);
	irmo_return_if_fail(variable != NULL);
	irmo_return_if_fail(value != NULL);


        irmo_return_if_fail(irmo_object_is_a2(object, variable->klass));


        *value = object->variables[variable->index];
}
