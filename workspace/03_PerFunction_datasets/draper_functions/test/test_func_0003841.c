make_port(ScmClass *klass, int dir, int type)
{
    ScmPort *port;

    port = SCM_ALLOCATE(ScmPort, klass);
    SCM_SET_CLASS(port, klass);
    port->direction = dir;
    port->type = type;
    port->scrcnt = 0;
    port->ungotten = SCM_CHAR_INVALID;
    port->closed = FALSE;
    port->error = FALSE;
    port->ownerp = FALSE;
    port->flags =
        SCM_VM_RUNTIME_FLAG_IS_SET(Scm_VM(), SCM_CASE_FOLD)
        ? SCM_PORT_CASE_FOLD
        : 0;
    port->name = SCM_FALSE;
    (void)SCM_INTERNAL_FASTLOCK_INIT(port->lock);
    port->lockOwner = NULL;
    port->lockCount = 0;
    port->data = SCM_FALSE;
    port->line = 1;
    switch (type) {
    case SCM_PORT_FILE: ;
    case SCM_PORT_PROC:
        Scm_RegisterFinalizer(SCM_OBJ(port), port_finalize, NULL);
        break;
    default:
        break;
    }
    return port;
}
