_modbus_set_slave(modbus_t *ctx, int slave)
{

    if (slave >= 0 && slave <= 247) {
        ctx->slave = slave;
    } else {
        errno = EINVAL;
        return -1;
    }

    return 0;
}
