pllib_devinit(void)
{
    if (plsc->dev_initialized) return;
    plsc->dev_initialized = 1;

    plSelectDev();

    plLoadDriver();


    plsc->dispatch_table = dispatch_table[plsc->device - 1];
}
