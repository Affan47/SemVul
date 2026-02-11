VALUE_default(VALUE *value, TYPE type)
{
	static void *jump[16] = {
		&&__VOID, &&__BOOLEAN, &&__BYTE, &&__SHORT, &&__INTEGER, &&__LONG, &&__SINGLE, &&__FLOAT, &&__DATE,
		&&__STRING, &&__STRING, &&__POINTER, &&__VARIANT, &&__FUNCTION, &&__CLASS, &&__NULL
		};

	value->type = type;

	if (TYPE_is_object(type))
		goto __OBJECT;
	else
		goto *jump[type];

__BOOLEAN:
__BYTE:
__SHORT:
__INTEGER:

	value->_integer.value = 0;
	return;

__LONG:

	value->_long.value = 0;
	return;

__SINGLE:
	value->_single.value = 0;
	return;

__FLOAT:
	value->_float.value = 0;
	return;

__STRING:
	value->_string.addr = NULL;
	value->_string.start = 0;
	value->_string.len = 0;
	return;

__VARIANT:
	value->_variant.vtype = T_NULL;
	return;

__POINTER:
	value->_pointer.value = NULL;
	return;

__DATE:
	value->_date.date = 0;
	value->_date.time = 0;
	return;

__VOID:
	return;

__OBJECT:
	value->_object.class = (CLASS *)type;
	value->_object.object = NULL;
	return;

__FUNCTION:
__CLASS:
__NULL:
	ERROR_panic("VALUE_default: Unknown default type");
}
