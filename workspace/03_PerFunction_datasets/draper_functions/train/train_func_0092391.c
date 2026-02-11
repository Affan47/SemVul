mmap_object_dealloc(mmap_object *m_obj)
{
#ifdef MS_WINDOWS
    if (m_obj->data != NULL)
        UnmapViewOfFile (m_obj->data);
    if (m_obj->map_handle != NULL)
        CloseHandle (m_obj->map_handle);
    if (m_obj->file_handle != INVALID_HANDLE_VALUE)
        CloseHandle (m_obj->file_handle);
    if (m_obj->tagname)
        PyMem_Free(m_obj->tagname);
#endif

#ifdef UNIX
    if (m_obj->fd >= 0)
        (void) close(m_obj->fd);
    if (m_obj->data!=NULL) {
        munmap(m_obj->data, m_obj->size);
    }
#endif

    Py_TYPE(m_obj)->tp_free((PyObject*)m_obj);
}
