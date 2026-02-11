_pickle_Pickler_clear_memo_impl(PicklerObject *self)

{
    if (self->memo)
        PyMemoTable_Clear(self->memo);

    Py_RETURN_NONE;
}
