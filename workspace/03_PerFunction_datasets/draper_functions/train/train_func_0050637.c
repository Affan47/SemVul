DisableAsyncReaderWrapper(GDALAsyncReaderWrapperH hWrapper)
{
    GDALAsyncReaderWrapper* psWrapper = (GDALAsyncReaderWrapper*)hWrapper;
    if (psWrapper->pyObject)
    {
        Py_XDECREF((PyObject*) psWrapper->pyObject);
    }
    psWrapper->pyObject = NULL;
    psWrapper->hAsyncReader = NULL;
}
