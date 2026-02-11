vector_command(int cmd)
{
    CharstringProgram::VectorType which_vector;
    int vectoroff, offset, num, i;
    Vector<double> *v = 0;

    switch (cmd) {

      case Cs::cPut:
	CHECK_STACK(2);
	offset = (int)top(0);
	vec(&_scratch_vector, offset) = top(1);
	pop(2);
	break;

      case Cs::cGet:
	CHECK_STACK(1);
	offset = (int)top();
	top() = vec(&_scratch_vector, offset);
	break;

      case Cs::cStore:
	CHECK_STACK(4);
	which_vector = (CharstringProgram::VectorType)((int)top(3));
	vectoroff = (int)top(2);
	offset = (int)top(1);
	num = (int)top(0);
	pop(4);

	if (!_program)
	    return error(errVector, cmd);
	v = _program->mm_vector(which_vector, true);
	if (!v)
	    return error(errVector, cmd);

	for (i = 0; i < num; i++, offset++, vectoroff++)
	    vec(v, vectoroff) = vec(&_scratch_vector, offset);

	if (which_vector == CharstringProgram::VEC_WEIGHT)
	    _weight_vector.clear();
	break;

      case Cs::cLoad:
	CHECK_STACK(3);
	which_vector = (CharstringProgram::VectorType)((int)top(2));
	offset = (int)top(1);
	num = (int)top(0);
	pop(3);

	if (!_program)
	    return error(errVector, cmd);
	v = _program->mm_vector(which_vector, false);

	if (!v && which_vector == CharstringProgram::VEC_WEIGHT && _weight_vector.size())
	    v = &_weight_vector;
	if (!v)
	    return error(errVector, cmd);

	for (i = 0; i < num; i++, offset++)
	    vec(&_scratch_vector, offset) = vec(v, i);
	break;

      default:
	return error(errUnimplemented, cmd);

    }

    return true;
}
