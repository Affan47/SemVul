point2DToPythonTuple(Point2D const & point)
{
    python_ptr tuple(PyTuple_New(2), python_ptr::keep_count);
    pythonToCppException(tuple);
    PyTuple_SET_ITEM((PyTupleObject *)tuple.get(), 0 ,pythonFromData(point.x).release());
    PyTuple_SET_ITEM((PyTupleObject *)tuple.get(), 1 ,pythonFromData(point.y).release());
    return tuple;
}
