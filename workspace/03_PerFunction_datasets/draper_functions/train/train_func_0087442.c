module_traverse(PyModuleObject *m, visitproc visit, void *arg)
{
    if (m->md_def && m->md_def->m_traverse) {
        int res = m->md_def->m_traverse((PyObject*)m, visit, arg);
        if (res)
            return res;
    }
    Py_VISIT(m->md_dict);
    return 0;
}
