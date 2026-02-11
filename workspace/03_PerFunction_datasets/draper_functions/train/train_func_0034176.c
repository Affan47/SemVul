InitDriver(opl_driver_t *_driver, unsigned int port_base)
{


    if (!_driver->init_func(port_base))
    {
        return 0;
    }


    driver = _driver;
    init_stage_reg_writes = 1;

    if (!OPL_Detect() || !OPL_Detect())
    {
        printf("OPL_Init: No OPL detected using '%s' driver.\n", _driver->name);
        _driver->shutdown_func();
        driver = NULL;
        return 0;
    }


    OPL_InitRegisters();

    init_stage_reg_writes = 0;

    printf("OPL_Init: Using driver '%s'.\n", driver->name);

    return 1;
}
