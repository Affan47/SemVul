fileport_inspect(ScmFilePort *port)
{
    char *combined;
    size_t size;

    if (port->aux_info) {
        size = sizeof("file ") + strlen(port->aux_info);
        combined = SCM_PORT_MALLOC(size);
        sprintf(combined, "file %s", port->aux_info);
        return combined;
    } else {
        return SCM_PORT_STRDUP("file");
    }
}
