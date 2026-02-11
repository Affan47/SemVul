rxgen_setproc_int2char(rxgen* object, RXGEN_PROC_INT2CHAR proc)
{
    if (object)
	object->int2char = proc ? proc : default_int2char;
}
