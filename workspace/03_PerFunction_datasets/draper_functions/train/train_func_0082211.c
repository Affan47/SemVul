gncEmployeeFree (GncEmployee *employee)
{
    if (!employee) return;

    qof_event_gen (&employee->inst, QOF_EVENT_DESTROY, NULL);

    CACHE_REMOVE (employee->id);
    CACHE_REMOVE (employee->username);
    CACHE_REMOVE (employee->language);
    CACHE_REMOVE (employee->acl);
    gncAddressBeginEdit (employee->addr);
    gncAddressDestroy (employee->addr);


    g_object_unref (employee);
}
