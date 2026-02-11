read(QIODevice *device)
{
    clear();

    if (!device->isOpen())
        device->open(QIODevice::ReadOnly);

    setDevice(device);
    return read();
}
