CORBA_sequence_CORBA_string_copy (CORBA_sequence_CORBA_string       *copy,
                                  const CORBA_sequence_CORBA_string *original)
{
	int i;

	copy->_maximum = original->_length;
	copy->_length = original->_length;
	copy->_buffer = CORBA_sequence_CORBA_string_allocbuf (original->_length);

	for (i = 0; i < original->_length; i++) {
		copy->_buffer[i] = CORBA_string_dup (original->_buffer[i]);
	}

	CORBA_sequence_set_release (copy, TRUE);
}
