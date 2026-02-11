_wrap_gst_rtsp_media_factory_get_launch(PyGObject *self)
{
    gchar *ret;

    pyg_begin_allow_threads;
    ret = gst_rtsp_media_factory_get_launch(GST_RTSP_MEDIA_FACTORY(self->obj));
    pyg_end_allow_threads;
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}
